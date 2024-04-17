// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Autogenerated from Pigeon (v18.0.0), do not edit directly.
// See also: https://pub.dev/packages/pigeon

#import <Foundation/Foundation.h>

@protocol FlutterBinaryMessenger;
@protocol FlutterMessageCodec;
@class FlutterError;
@class FlutterStandardTypedData;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, FCPPlatformCameraLensDirection) {
  /// Front facing camera (a user looking at the screen is seen by the camera).
  FCPPlatformCameraLensDirectionFront = 0,
  /// Back facing camera (a user looking at the screen is not seen by the camera).
  FCPPlatformCameraLensDirectionBack = 1,
  /// External camera which may not be mounted to the device.
  FCPPlatformCameraLensDirectionExternal = 2,
};

/// Wrapper for FCPPlatformCameraLensDirection to allow for nullability.
@interface FCPPlatformCameraLensDirectionBox : NSObject
@property(nonatomic, assign) FCPPlatformCameraLensDirection value;
- (instancetype)initWithValue:(FCPPlatformCameraLensDirection)value;
@end

typedef NS_ENUM(NSUInteger, FCPPlatformDeviceOrientation) {
  FCPPlatformDeviceOrientationPortraitUp = 0,
  FCPPlatformDeviceOrientationLandscapeLeft = 1,
  FCPPlatformDeviceOrientationPortraitDown = 2,
  FCPPlatformDeviceOrientationLandscapeRight = 3,
};

/// Wrapper for FCPPlatformDeviceOrientation to allow for nullability.
@interface FCPPlatformDeviceOrientationBox : NSObject
@property(nonatomic, assign) FCPPlatformDeviceOrientation value;
- (instancetype)initWithValue:(FCPPlatformDeviceOrientation)value;
@end

@class FCPPlatformCameraDescription;

@interface FCPPlatformCameraDescription : NSObject
/// `init` unavailable to enforce nonnull fields, see the `make` class method.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)makeWithName:(NSString *)name
               lensDirection:(FCPPlatformCameraLensDirection)lensDirection;
/// The name of the camera device.
@property(nonatomic, copy) NSString *name;
/// The direction the camera is facing.
@property(nonatomic, assign) FCPPlatformCameraLensDirection lensDirection;
@end

/// The codec used by FCPCameraApi.
NSObject<FlutterMessageCodec> *FCPCameraApiGetCodec(void);

@protocol FCPCameraApi
/// Returns the list of available cameras.
- (void)availableCamerasWithCompletion:(void (^)(NSArray<FCPPlatformCameraDescription *> *_Nullable,
                                                 FlutterError *_Nullable))completion;
@end

extern void SetUpFCPCameraApi(id<FlutterBinaryMessenger> binaryMessenger,
                              NSObject<FCPCameraApi> *_Nullable api);

extern void SetUpFCPCameraApiWithSuffix(id<FlutterBinaryMessenger> binaryMessenger,
                                        NSObject<FCPCameraApi> *_Nullable api,
                                        NSString *messageChannelSuffix);

/// The codec used by FCPCameraGlobalEventApi.
NSObject<FlutterMessageCodec> *FCPCameraGlobalEventApiGetCodec(void);

/// Handler for native callbacks that are not tied to a specific camera ID.
@interface FCPCameraGlobalEventApi : NSObject
- (instancetype)initWithBinaryMessenger:(id<FlutterBinaryMessenger>)binaryMessenger;
- (instancetype)initWithBinaryMessenger:(id<FlutterBinaryMessenger>)binaryMessenger
                   messageChannelSuffix:(nullable NSString *)messageChannelSuffix;
/// Called when the device's physical orientation changes.
- (void)deviceOrientationChangedOrientation:(FCPPlatformDeviceOrientation)orientation
                                 completion:(void (^)(FlutterError *_Nullable))completion;
@end

NS_ASSUME_NONNULL_END
