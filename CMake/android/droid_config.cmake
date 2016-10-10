########################################
# Required env var:
# - ANDROID_SDK: path to the Android SDK
# - ANDROID_NDK: path to the Android NDK
# - JAVA_HOME: path to Java SDK

########################################
# Find Android NDK
if(DEFINED ENV{ANDROID_NDK})
    set(ANDROID_NDK "$ENV{ANDROID_NDK}" CACHE PATH "Path to the Android NDK")
else()
    message(FATAL_ERROR "Can not find android NDK path, please set the path in env var 'ANDROID_NDK'")
endif()
file(TO_CMAKE_PATH "${ANDROID_NDK}" ANDROID_NDK)
# for compatibility with taka-no-me toolchain
set(ANDROID_NDK ${ANDROID_NDK})

########################################
# Find Android SDK
if(DEFINED ENV{ANDROID_SDK})
    set(ANDROID_SDK_PATH "$ENV{ANDROID_SDK}" CACHE PATH "Path to the Android SDK")
else()
    message(FATAL_ERROR "Can not find android SDK path, please set the path in env var 'ANDROID_SDK'")
endif()
file(TO_CMAKE_PATH "${ANDROID_SDK_PATH}" ANDROID_SDK_PATH)

########################################
# macro to find packages on the host OS
macro(find_host_package )
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER )
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER )
    if(CMAKE_HOST_WIN32 )
        set(WIN32 1 )
        set(UNIX )
    elseif( CMAKE_HOST_APPLE )
        set(APPLE 1 )
        set(UNIX )
    endif()
    find_package( ${ARGN} )
    set(WIN32 )
    set(APPLE )
    set(UNIX 1 )
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
endmacro()

# macro to find programs on the host OS
macro(find_host_program )
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER )
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER )
    if(CMAKE_HOST_WIN32 )
        set(WIN32 1 )
        set(UNIX )
    elseif(CMAKE_HOST_APPLE )
        set(APPLE 1 )
        set(UNIX )
    endif()
    find_program( ${ARGN} )
    set(WIN32 )
    set(APPLE )
    set(UNIX 1 )
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
endmacro()

########################################
# detect current host platform
if(NOT DEFINED ANDROID_NDK_HOST_X64 AND (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "amd64|x86_64|AMD64" OR CMAKE_HOST_APPLE) )
 set(ANDROID_NDK_HOST_X64 1 CACHE BOOL "Try to use 64-bit compiler toolchain" )
 mark_as_advanced( ANDROID_NDK_HOST_X64 )
endif()

set(TOOL_OS_SUFFIX "" )
if(CMAKE_HOST_APPLE )
 set(ANDROID_NDK_HOST_SYSTEM_NAME "darwin-x86_64" )
 set(ANDROID_NDK_HOST_SYSTEM_NAME2 "darwin-x86" )
elseif(CMAKE_HOST_WIN32 )
 set(ANDROID_NDK_HOST_SYSTEM_NAME "windows-x86_64" )
 set(ANDROID_NDK_HOST_SYSTEM_NAME2 "windows" )
 set(TOOL_OS_SUFFIX ".exe" )
elseif(CMAKE_HOST_UNIX )
 set(ANDROID_NDK_HOST_SYSTEM_NAME "linux-x86_64" )
 set(ANDROID_NDK_HOST_SYSTEM_NAME2 "linux-x86" )
else()
 message( FATAL_ERROR "Cross-compilation on your platform is not supported by this cmake toolchain" )
endif()

if(NOT ANDROID_NDK_HOST_X64 )
 set(ANDROID_NDK_HOST_SYSTEM_NAME ${ANDROID_NDK_HOST_SYSTEM_NAME2} )
endif()

########################################
# Find Android command line tool
find_host_program(ANDROID_PRG
    NAMES android android.bat
    PATHS "${ANDROID_SDK_PATH}/tools"
    DOC   "The android command-line tool"
)
if(NOT ANDROID_PRG)
    message(FATAL_ERROR "Can not find android command line tool: android")
endif()

########################################
# Find adb
find_host_program(ADB_PRG
    NAMES adb
    PATHS "${ANDROID_SDK_PATH}/platform-tools"
    DOC   "The adb install tool"
)
if(NOT ADB_PRG)
    message(FATAL_ERROR "Can not find ant build tool: adb")
endif()

########################################
# Find ndk-depends
find_host_program(NDK_DEPENDS_PRG
    NAMES ndk-depends
    PATHS ${ANDROID_NDK} "${ANDROID_NDK}/prebuilt/windows-x86_64/bin"
    DOC   "The ndk-depends command-line tool"
)
if(NOT NDK_DEPENDS_PRG)
    message(FATAL_ERROR "Can not find android command line tool: ndk-depends")
endif()

########################################
# Find jarsigner
file(TO_CMAKE_PATH "$ENV{JAVA_HOME}" JAVA_HOME_PATH)
find_host_program(JARSIGNER_PRG
    NAMES jarsigner jarsigner.exe
    PATHS "${JAVA_HOME_PATH}/bin/"
    DOC  "The jarsigner tool (in jdk/bin/)"
)
if(NOT JARSIGNER_PRG)
    message(FATAL_ERROR "Can not find jarsigner tool")
endif()

########################################
# Find zipalign
file(GLOB BUILD_TOOLS_CHILDREN "${ANDROID_SDK_PATH}/build-tools/*")
set(BUILD_TOOLS_DIRLIST)
foreach(BUILD_TOOLS_CHILD ${BUILD_TOOLS_CHILDREN})
    if(IS_DIRECTORY "${BUILD_TOOLS_CHILD}")
        list(APPEND BUILD_TOOLS_DIRLIST ${BUILD_TOOLS_CHILD})
    endif()
endforeach()

find_host_program(ZIPALIGN_PRG
    NAMES zipalign zipalign.exe
    PATHS ${BUILD_TOOLS_DIRLIST}
    DOC "The zipalign tool")
if (NOT ZIPALIGN_PRG)
    message(FATAL_ERROR "zipalign command is not found.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(APK_BUILD_TOOL               "gradle"                    CACHE STRING    "Build tool name will be used to create the apk (ant or gradle)")
set(ANDROID_APK_RELEASE          "0"                         CACHE BOOL      "Create apk file ready for release? (signed, you have to enter a password during build, do also setup \"ANDROID_APK_SIGNER_KEYSTORE\" and \"ANDROID_APK_SIGNER_ALIAS\")")
set(ANDROID_APK_TOP_LEVEL_DOMAIN "com"                       CACHE STRING    "Top level domain name of the organization (follow the package naming conventions (http://en.wikipedia.org/wiki/Java_package#Package_naming_conventions))")
set(ANDROID_APK_DOMAIN           "fw4spl"                    CACHE STRING    "Organization's domain (follow the package naming conventions (http://en.wikipedia.org/wiki/Java_package#Package_naming_conventions))")
set(ANDROID_APK_KEYSTORE         "~/keystore/android.jks"    CACHE PATH      "Keystore for signing the apk file (only required for release apk)")
set(ANDROID_APK_KEYSTORE_PWD     "123456"                    CACHE STRING    "Keystore password (only required for release apk)")
set(ANDROID_APK_KEY_ALIAS        "keyAlias"                  CACHE STRING    "Alias for signing the apk file (only required for release apk)")
set(ANDROID_APK_KEY_PWD          "123456"                    CACHE STRING    "Alias password (only required for release apk)")

set(CMAKE_ANDROID_APK_PACKAGE \"${ANDROID_APK_TOP_LEVEL_DOMAIN}/${ANDROID_APK_DOMAIN}/${PROJECTS_TO_INSTALL}\" PARENT_SCOPE)
set(PACKAGE_DOT ${ANDROID_APK_TOP_LEVEL_DOMAIN}.${ANDROID_APK_DOMAIN}.${PROJECTS_TO_INSTALL} PARENT_SCOPE)

file(TO_CMAKE_PATH "${ANDROID_APK_KEYSTORE}" ANDROID_APK_KEYSTORE) #fix issue on Windows host


if( ${APK_BUILD_TOOL} STREQUAL "ant" )
    ########################################
    # Find ant
    find_host_program(ANT_PRG
        NAMES ant.bat ant
        PATHS /usr/bin/
        DOC   "The ant build tool")
    if(NOT ANT_PRG)
        message(FATAL_ERROR "Can not find ant build tool: ant")
    endif()
elseif( ${APK_BUILD_TOOL} STREQUAL "gradle" )
    ########################################
    # Find gradle
    find_host_program(GRADLE_PRG
        NAMES gradle.bat gradle
        PATHS /usr/bin/
        DOC   "The gradle build tool")
    if(NOT GRADLE_PRG)
        message(FATAL_ERROR "Can not find ant build tool: gradle")
    endif()
else()
    message(FATAL_ERROR "Unknown apk build tool \"${APK_BUILD_TOOL}\". Set ant or gradle")
endif()

