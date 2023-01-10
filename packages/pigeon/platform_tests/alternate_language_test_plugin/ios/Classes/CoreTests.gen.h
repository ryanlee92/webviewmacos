// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Autogenerated from Pigeon (v5.0.1), do not edit directly.
// See also: https://pub.dev/packages/pigeon
#import <Foundation/Foundation.h>
@protocol FlutterBinaryMessenger;
@protocol FlutterMessageCodec;
@class FlutterError;
@class FlutterStandardTypedData;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AnEnum) {
  AnEnumOne = 0,
  AnEnumTwo = 1,
  AnEnumThree = 2,
};

@class AllTypes;
@class AllNullableTypes;
@class AllNullableTypesWrapper;

@interface AllTypes : NSObject
/// `init` unavailable to enforce nonnull fields, see the `make` class method.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)makeWithABool:(NSNumber *)aBool
                        anInt:(NSNumber *)anInt
                      aDouble:(NSNumber *)aDouble
                      aString:(NSString *)aString
                   aByteArray:(FlutterStandardTypedData *)aByteArray
                  a4ByteArray:(FlutterStandardTypedData *)a4ByteArray
                  a8ByteArray:(FlutterStandardTypedData *)a8ByteArray
                  aFloatArray:(FlutterStandardTypedData *)aFloatArray
                        aList:(NSArray *)aList
                         aMap:(NSDictionary *)aMap
                       anEnum:(AnEnum)anEnum;
@property(nonatomic, strong) NSNumber *aBool;
@property(nonatomic, strong) NSNumber *anInt;
@property(nonatomic, strong) NSNumber *aDouble;
@property(nonatomic, copy) NSString *aString;
@property(nonatomic, strong) FlutterStandardTypedData *aByteArray;
@property(nonatomic, strong) FlutterStandardTypedData *a4ByteArray;
@property(nonatomic, strong) FlutterStandardTypedData *a8ByteArray;
@property(nonatomic, strong) FlutterStandardTypedData *aFloatArray;
@property(nonatomic, strong) NSArray *aList;
@property(nonatomic, strong) NSDictionary *aMap;
@property(nonatomic, assign) AnEnum anEnum;
@end

@interface AllNullableTypes : NSObject
+ (instancetype)makeWithANullableBool:(nullable NSNumber *)aNullableBool
                         aNullableInt:(nullable NSNumber *)aNullableInt
                      aNullableDouble:(nullable NSNumber *)aNullableDouble
                      aNullableString:(nullable NSString *)aNullableString
                   aNullableByteArray:(nullable FlutterStandardTypedData *)aNullableByteArray
                  aNullable4ByteArray:(nullable FlutterStandardTypedData *)aNullable4ByteArray
                  aNullable8ByteArray:(nullable FlutterStandardTypedData *)aNullable8ByteArray
                  aNullableFloatArray:(nullable FlutterStandardTypedData *)aNullableFloatArray
                        aNullableList:(nullable NSArray *)aNullableList
                         aNullableMap:(nullable NSDictionary *)aNullableMap
                   nullableNestedList:(nullable NSArray<NSArray<NSNumber *> *> *)nullableNestedList
           nullableMapWithAnnotations:
               (nullable NSDictionary<NSString *, NSString *> *)nullableMapWithAnnotations
                nullableMapWithObject:(nullable NSDictionary<NSString *, id> *)nullableMapWithObject
                        aNullableEnum:(AnEnum)aNullableEnum;
@property(nonatomic, strong, nullable) NSNumber *aNullableBool;
@property(nonatomic, strong, nullable) NSNumber *aNullableInt;
@property(nonatomic, strong, nullable) NSNumber *aNullableDouble;
@property(nonatomic, copy, nullable) NSString *aNullableString;
@property(nonatomic, strong, nullable) FlutterStandardTypedData *aNullableByteArray;
@property(nonatomic, strong, nullable) FlutterStandardTypedData *aNullable4ByteArray;
@property(nonatomic, strong, nullable) FlutterStandardTypedData *aNullable8ByteArray;
@property(nonatomic, strong, nullable) FlutterStandardTypedData *aNullableFloatArray;
@property(nonatomic, strong, nullable) NSArray *aNullableList;
@property(nonatomic, strong, nullable) NSDictionary *aNullableMap;
@property(nonatomic, strong, nullable) NSArray<NSArray<NSNumber *> *> *nullableNestedList;
@property(nonatomic, strong, nullable)
    NSDictionary<NSString *, NSString *> *nullableMapWithAnnotations;
@property(nonatomic, strong, nullable) NSDictionary<NSString *, id> *nullableMapWithObject;
@property(nonatomic, assign) AnEnum aNullableEnum;
@end

@interface AllNullableTypesWrapper : NSObject
/// `init` unavailable to enforce nonnull fields, see the `make` class method.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)makeWithValues:(AllNullableTypes *)values;
@property(nonatomic, strong) AllNullableTypes *values;
@end

/// The codec used by HostIntegrationCoreApi.
NSObject<FlutterMessageCodec> *HostIntegrationCoreApiGetCodec(void);

/// The core interface that each host language plugin must implement in
/// platform_test integration tests.
@protocol HostIntegrationCoreApi
/// A no-op function taking no arguments and returning no value, to sanity
/// test basic calling.
- (void)noopWithError:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed object, to test serialization and deserialization.
///
/// @return `nil` only when `error != nil`.
- (nullable AllTypes *)echoAllTypes:(AllTypes *)everything
                              error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed object, to test serialization and deserialization.
- (nullable AllNullableTypes *)echoAllNullableTypes:(nullable AllNullableTypes *)everything
                                              error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns an error, to test error handling.
- (void)throwErrorWithError:(FlutterError *_Nullable *_Nonnull)error;
/// Returns passed in int.
///
/// @return `nil` only when `error != nil`.
- (nullable NSNumber *)echoInt:(NSNumber *)anInt error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns passed in double.
///
/// @return `nil` only when `error != nil`.
- (nullable NSNumber *)echoDouble:(NSNumber *)aDouble
                            error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in boolean.
///
/// @return `nil` only when `error != nil`.
- (nullable NSNumber *)echoBool:(NSNumber *)aBool error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in string.
///
/// @return `nil` only when `error != nil`.
- (nullable NSString *)echoString:(NSString *)aString
                            error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in Uint8List.
///
/// @return `nil` only when `error != nil`.
- (nullable FlutterStandardTypedData *)echoUint8List:(FlutterStandardTypedData *)aUint8List
                                               error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in generic Object.
///
/// @return `nil` only when `error != nil`.
- (nullable id)echoObject:(id)anObject error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the inner `aString` value from the wrapped object, to test
/// sending of nested objects.
- (nullable NSString *)extractNestedNullableStringFrom:(AllNullableTypesWrapper *)wrapper
                                                 error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the inner `aString` value from the wrapped object, to test
/// sending of nested objects.
///
/// @return `nil` only when `error != nil`.
- (nullable AllNullableTypesWrapper *)
    createNestedObjectWithNullableString:(nullable NSString *)nullableString
                                   error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns passed in arguments of multiple types.
///
/// @return `nil` only when `error != nil`.
- (nullable AllNullableTypes *)sendMultipleNullableTypesABool:(nullable NSNumber *)aNullableBool
                                                        anInt:(nullable NSNumber *)aNullableInt
                                                      aString:(nullable NSString *)aNullableString
                                                        error:(FlutterError *_Nullable *_Nonnull)
                                                                  error;
/// Returns passed in int.
- (nullable NSNumber *)echoNullableInt:(nullable NSNumber *)aNullableInt
                                 error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns passed in double.
- (nullable NSNumber *)echoNullableDouble:(nullable NSNumber *)aNullableDouble
                                    error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in boolean.
- (nullable NSNumber *)echoNullableBool:(nullable NSNumber *)aNullableBool
                                  error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in string.
- (nullable NSString *)echoNullableString:(nullable NSString *)aNullableString
                                    error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in Uint8List.
- (nullable FlutterStandardTypedData *)
    echoNullableUint8List:(nullable FlutterStandardTypedData *)aNullableUint8List
                    error:(FlutterError *_Nullable *_Nonnull)error;
/// Returns the passed in generic Object.
- (nullable id)echoNullableObject:(nullable id)aNullableObject
                            error:(FlutterError *_Nullable *_Nonnull)error;
/// A no-op function taking no arguments and returning no value, to sanity
/// test basic asynchronous calling.
- (void)noopAsyncWithCompletion:(void (^)(FlutterError *_Nullable))completion;
/// Returns the passed string asynchronously.
- (void)echoAsyncString:(NSString *)aString
             completion:(void (^)(NSString *_Nullable, FlutterError *_Nullable))completion;
- (void)callFlutterNoopWithCompletion:(void (^)(FlutterError *_Nullable))completion;
- (void)callFlutterEchoString:(NSString *)aString
                   completion:(void (^)(NSString *_Nullable, FlutterError *_Nullable))completion;
@end

extern void HostIntegrationCoreApiSetup(id<FlutterBinaryMessenger> binaryMessenger,
                                        NSObject<HostIntegrationCoreApi> *_Nullable api);

/// The codec used by FlutterIntegrationCoreApi.
NSObject<FlutterMessageCodec> *FlutterIntegrationCoreApiGetCodec(void);

/// The core interface that the Dart platform_test code implements for host
/// integration tests to call into.
@interface FlutterIntegrationCoreApi : NSObject
- (instancetype)initWithBinaryMessenger:(id<FlutterBinaryMessenger>)binaryMessenger;
/// A no-op function taking no arguments and returning no value, to sanity
/// test basic calling.
- (void)noopWithCompletion:(void (^)(NSError *_Nullable))completion;
/// Returns the passed object, to test serialization and deserialization.
- (void)echoAllTypes:(AllTypes *)everything
          completion:(void (^)(AllTypes *_Nullable, NSError *_Nullable))completion;
/// Returns the passed object, to test serialization and deserialization.
- (void)echoAllNullableTypes:(AllNullableTypes *)everything
                  completion:(void (^)(AllNullableTypes *_Nullable, NSError *_Nullable))completion;
/// Returns passed in arguments of multiple types.
///
/// Tests multiple-arity FlutterApi handling.
- (void)sendMultipleNullableTypesABool:(nullable NSNumber *)aNullableBool
                                 anInt:(nullable NSNumber *)aNullableInt
                               aString:(nullable NSString *)aNullableString
                            completion:(void (^)(AllNullableTypes *_Nullable,
                                                 NSError *_Nullable))completion;
/// Returns the passed boolean, to test serialization and deserialization.
- (void)echoBool:(NSNumber *)aBool
      completion:(void (^)(NSNumber *_Nullable, NSError *_Nullable))completion;
/// Returns the passed int, to test serialization and deserialization.
- (void)echoInt:(NSNumber *)anInt
     completion:(void (^)(NSNumber *_Nullable, NSError *_Nullable))completion;
/// Returns the passed double, to test serialization and deserialization.
- (void)echoDouble:(NSNumber *)aDouble
        completion:(void (^)(NSNumber *_Nullable, NSError *_Nullable))completion;
/// Returns the passed string, to test serialization and deserialization.
- (void)echoString:(NSString *)aString
        completion:(void (^)(NSString *_Nullable, NSError *_Nullable))completion;
/// Returns the passed byte list, to test serialization and deserialization.
- (void)echoUint8List:(FlutterStandardTypedData *)aList
           completion:(void (^)(FlutterStandardTypedData *_Nullable, NSError *_Nullable))completion;
/// Returns the passed list, to test serialization and deserialization.
- (void)echoList:(NSArray<id> *)aList
      completion:(void (^)(NSArray<id> *_Nullable, NSError *_Nullable))completion;
/// Returns the passed map, to test serialization and deserialization.
- (void)echoMap:(NSDictionary<NSString *, id> *)aMap
     completion:(void (^)(NSDictionary<NSString *, id> *_Nullable, NSError *_Nullable))completion;
/// Returns the passed boolean, to test serialization and deserialization.
- (void)echoNullableBool:(nullable NSNumber *)aBool
              completion:(void (^)(NSNumber *_Nullable, NSError *_Nullable))completion;
/// Returns the passed int, to test serialization and deserialization.
- (void)echoNullableInt:(nullable NSNumber *)anInt
             completion:(void (^)(NSNumber *_Nullable, NSError *_Nullable))completion;
/// Returns the passed double, to test serialization and deserialization.
- (void)echoNullableDouble:(nullable NSNumber *)aDouble
                completion:(void (^)(NSNumber *_Nullable, NSError *_Nullable))completion;
/// Returns the passed string, to test serialization and deserialization.
- (void)echoNullableString:(nullable NSString *)aString
                completion:(void (^)(NSString *_Nullable, NSError *_Nullable))completion;
/// Returns the passed byte list, to test serialization and deserialization.
- (void)echoNullableUint8List:(nullable FlutterStandardTypedData *)aList
                   completion:(void (^)(FlutterStandardTypedData *_Nullable,
                                        NSError *_Nullable))completion;
/// Returns the passed list, to test serialization and deserialization.
- (void)echoNullableList:(nullable NSArray<id> *)aList
              completion:(void (^)(NSArray<id> *_Nullable, NSError *_Nullable))completion;
/// Returns the passed map, to test serialization and deserialization.
- (void)echoNullableMap:(NSDictionary<NSString *, id> *)aMap
             completion:
                 (void (^)(NSDictionary<NSString *, id> *_Nullable, NSError *_Nullable))completion;
@end
/// The codec used by HostTrivialApi.
NSObject<FlutterMessageCodec> *HostTrivialApiGetCodec(void);

/// An API that can be implemented for minimal, compile-only tests.
@protocol HostTrivialApi
- (void)noopWithError:(FlutterError *_Nullable *_Nonnull)error;
@end

extern void HostTrivialApiSetup(id<FlutterBinaryMessenger> binaryMessenger,
                                NSObject<HostTrivialApi> *_Nullable api);

NS_ASSUME_NONNULL_END
