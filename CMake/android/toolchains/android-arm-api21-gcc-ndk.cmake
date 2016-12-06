# Android gcc toolchain file for Android NDK >= 13

set(ANDROID_TOOLCHAIN gcc)
set(ANDROID_ABI armeabi-v7a)
set(ANDROID_NATIVE_API_LEVEL 21)
set(ANDROID_PLATFORM android-21)
set(ANDROID_STL gnustl_shared)
#set(ANDROID_STL c++_shared)
set(ANDROID_CPP_FEATURES "rtti exceptions")
set(ANDROID_ALLOW_UNDEFINED_SYMBOLS FALSE)
set(ANDROID_ARM_NEON TRUE)

# Find Android NDK
if(DEFINED ENV{ANDROID_NDK})
    set(ANDROID_NDK "$ENV{ANDROID_NDK}" CACHE PATH "Path to the Android NDK")
else()
    message(FATAL_ERROR "Can not find android NDK path, please set the path in env var 'ANDROID_NDK'")
endif()
include(${ANDROID_NDK}/build/cmake/android.toolchain.cmake)

remove_definitions(-DANDROID)
add_definitions(-DANDROID)

# for compatibility with taka-no-me toolchain
set(ANDROID_API_LEVEL ${ANDROID_NATIVE_API_LEVEL}) 

# where is the target environment
set(CMAKE_FIND_ROOT_PATH 
    "${ANDROID_TOOLCHAIN_ROOT}/bin"
    "${ANDROID_TOOLCHAIN_ROOT}/${ANDROID_TOOLCHAIN_MACHINE_NAME}"
    "${ANDROID_SYSROOT}"
    "${CMAKE_INSTALL_PREFIX}"
    "${CMAKE_INSTALL_PREFIX}/share"
) 
include_directories(SYSTEM "${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}")