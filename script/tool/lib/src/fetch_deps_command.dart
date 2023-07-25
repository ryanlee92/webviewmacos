// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:file/file.dart';

import 'common/core.dart';
import 'common/gradle.dart';
import 'common/output_utils.dart';
import 'common/package_looping_command.dart';
import 'common/plugin_utils.dart';
import 'common/repository_package.dart';

const int _exitNothingRequested = 3;

/// Download dependencies, both Dart and native.
///
/// Specficially each platform runs:
///   Android: 'gradlew dependencies'.
///   Dart: 'flutter pub get'.
///   iOS/macOS: 'pod install'.
///
/// See https://docs.gradle.org/6.4/userguide/core_dependency_management.html#sec:dependency-mgmt-in-gradle.
class FetchDepsCommand extends PackageLoopingCommand {
  /// Creates an instance of the fetch-deps command.
  FetchDepsCommand(
    super.packagesDir, {
    super.processRunner,
    super.platform,
  }) {
    argParser.addFlag(_dartFlag, defaultsTo: true, help: 'Run "pub get"');
    argParser.addFlag(_supportingTargetPlatformsOnlyFlag,
        help: 'Restricted "pub get" runs to packages that have at least one '
            'example supporting at least one of the platform flags passed.\n'
            'If no platform flags are passed, this will exclude all packages.');
    argParser.addFlag(platformAndroid,
        help: 'Run "gradlew dependencies" for Android plugins.\n'
            'Include packages with Android examples when used with '
            '--$_supportingTargetPlatformsOnlyFlag');
    argParser.addFlag(platformIOS,
        help: 'Run "pod install" for iOS plugins.\n'
            'Include packages with iOS examples when used with '
            '--$_supportingTargetPlatformsOnlyFlag');
    argParser.addFlag(platformLinux,
        help: 'Include packages with Linux examples when used with '
            '--$_supportingTargetPlatformsOnlyFlag');
    argParser.addFlag(platformMacOS,
        help: 'Run "pod install" for macOS plugins.\n'
            'Include packages with macOS examples when used with '
            '--$_supportingTargetPlatformsOnlyFlag');
    argParser.addFlag(platformWeb,
        help: 'Include packages with Web examples when used with '
            '--$_supportingTargetPlatformsOnlyFlag');
    argParser.addFlag(platformWindows,
        help: 'Include packages with Windows examples when used with '
            '--$_supportingTargetPlatformsOnlyFlag');
  }

  static const String _dartFlag = 'dart';
  static const String _supportingTargetPlatformsOnlyFlag =
      'supporting-target-platforms-only';

  static const Iterable<String> _platforms = <String>[
    platformAndroid,
    platformIOS,
    platformLinux,
    platformMacOS,
    platformWeb,
    platformWindows,
  ];

  @override
  final String name = 'fetch-deps';

  @override
  final String description = 'Fetches dependencies for packages';

  @override
  Future<PackageResult> runForPackage(RepositoryPackage package) async {
    bool fetchedDeps = false;
    final List<String> skips = <String>[];
    if (getBoolArg(_dartFlag)) {
      final bool filterPlatforms =
          getBoolArg(_supportingTargetPlatformsOnlyFlag);
      if (!filterPlatforms || _hasExampleSupportingRequestedPlatform(package)) {
        fetchedDeps = true;
        if (!await _fetchDartPackages(package)) {
          // If Dart-level depenendencies fail, fail immediately since the
          // native dependencies won't be useful.
          return PackageResult.fail(<String>['Failed to "pub get".']);
        }
      } else {
        skips.add('Skipping Dart dependencies; no examples support requested '
            'platforms.');
      }
    }

    final List<String> errors = <String>[];
    for (final FlutterPlatform platform in _targetPlatforms) {
      final PackageResult result;
      switch (platform) {
        case FlutterPlatform.android:
          result = await _fetchAndroidDeps(package);
          break;
        case FlutterPlatform.ios:
          result = await _fetchDarwinDeps(package, platformIOS);
          break;
        case FlutterPlatform.macos:
          result = await _fetchDarwinDeps(package, platformMacOS);
          break;
        case FlutterPlatform.linux:
        case FlutterPlatform.web:
        case FlutterPlatform.windows:
          // No native dependency handling yet.
          result = PackageResult.skip('Nothing to do for $platform.');
          break;
      }
      switch (result.state) {
        case RunState.succeeded:
          fetchedDeps = true;
          break;
        case RunState.skipped:
          skips.add(result.details.first);
          break;
        case RunState.failed:
          errors.addAll(result.details);
          break;
        case RunState.excluded:
          throw StateError('Unreachable');
      }
    }

    if (errors.isNotEmpty) {
      return PackageResult.fail(errors);
    }
    if (fetchedDeps) {
      return PackageResult.success();
    }
    if (skips.isNotEmpty) {
      return PackageResult.skip(<String>['', ...skips].join('\n- '));
    }

    printError('At least one type of dependency must be requested');
    throw ToolExit(_exitNothingRequested);
  }

  Future<PackageResult> _fetchAndroidDeps(RepositoryPackage package) async {
    if (!pluginSupportsPlatform(platformAndroid, package,
        requiredMode: PlatformSupport.inline)) {
      return PackageResult.skip(
          'Package does not have native Android dependencies.');
    }

    for (final RepositoryPackage example in package.getExamples()) {
      final GradleProject gradleProject = GradleProject(example,
          processRunner: processRunner, platform: platform);

      if (!gradleProject.isConfigured()) {
        final int exitCode = await processRunner.runAndStream(
          flutterCommand,
          <String>['build', 'apk', '--config-only'],
          workingDir: example.directory,
        );
        if (exitCode != 0) {
          printError('Unable to configure Gradle project.');
          return PackageResult.fail(<String>['Unable to configure Gradle.']);
        }
      }

      final String packageName = package.directory.basename;

      final int exitCode =
          await gradleProject.runCommand('$packageName:dependencies');
      if (exitCode != 0) {
        return PackageResult.fail();
      }
    }

    return PackageResult.success();
  }

  Future<PackageResult> _fetchDarwinDeps(
      RepositoryPackage package, final String platform) async {
    if (!pluginSupportsPlatform(platform, package,
        requiredMode: PlatformSupport.inline)) {
      final String displayPlatform = platform.replaceFirst('os', 'OS');
      return PackageResult.skip(
          'Package does not have native $displayPlatform dependencies.');
    }

    for (final RepositoryPackage example in package.getExamples()) {
      final Directory platformDir =
          example.platformDirectory(getPlatformByName(platform));

      final File generatedXCConfig = platform == platformMacOS
          ? platformDir
              .childDirectory('Flutter')
              .childDirectory('ephemeral')
              .childFile('Flutter-Generated.xcconfig')
          : platformDir
              .childDirectory('Flutter')
              .childFile('Generated.xcconfig');
      // Running `pod install` requires `flutter pub get` or `flutter build` to
      // have been run at some point to create the necessary native build files.
      if (!generatedXCConfig.existsSync()) {
        final int exitCode = await processRunner.runAndStream(
          flutterCommand,
          <String>['pub', 'get'],
          workingDir: example.directory,
        );
        if (exitCode != 0) {
          printError('Unable to prepare native project files.');
          return PackageResult.fail(<String>['Unable to configure project.']);
        }
      }

      final int exitCode = await processRunner.runAndStream(
        'pod',
        <String>['install'],
        workingDir: platformDir,
      );
      if (exitCode != 0) {
        printError('Unable to "pod install"');
        return PackageResult.fail(<String>['Unable to "pod install"']);
      }
    }

    return PackageResult.success();
  }

  Future<bool> _fetchDartPackages(RepositoryPackage package) async {
    final String command = package.requiresFlutter() ? flutterCommand : 'dart';
    final int exitCode = await processRunner.runAndStream(
        command, <String>['pub', 'get'],
        workingDir: package.directory);
    return exitCode == 0;
  }

  bool _hasExampleSupportingRequestedPlatform(RepositoryPackage package) {
    return package.getExamples().any((RepositoryPackage example) {
      return _targetPlatforms.any(
          (FlutterPlatform platform) => example.appSupportsPlatform(platform));
    });
  }

  Iterable<FlutterPlatform> get _targetPlatforms => _platforms
      .where((String platform) => getBoolArg(platform))
      .map((String platformName) => getPlatformByName(platformName));
}
