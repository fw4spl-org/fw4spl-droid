# Android CLang toolchain file for Android arch armv7-a, API level 21

cmake_minimum_required(VERSION 3.7)

set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 21) # API level
set(CMAKE_ANDROID_ARCH_ABI armeabi-v7a)
set(CMAKE_ANDROID_ARM_NEON on)
# Find Android NDK
if(DEFINED ENV{ANDROID_NDK})
    set(CMAKE_ANDROID_NDK "$ENV{ANDROID_NDK}" CACHE PATH "Path to the Android NDK")
else()
    message(FATAL_ERROR "Can not find android NDK path, please set the path in env var 'ANDROID_NDK'")
endif()
set(CMAKE_ANDROID_STL_TYPE c++_shared)
set(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION clang)
remove_definitions( -DANDROID )
add_definitions( -DANDROID )

# for compatibility with taka-no-me toolchain
set(ANDROID_API_LEVEL ${CMAKE_SYSTEM_VERSION}) 

