if(ANDROID)

cmake_minimum_required (VERSION 2.8.11)

project (fw4spl-droid)

set(CROSS_COMPILING ON CACHE BOOL "Configure cross compilation")

if(CROSS_COMPILING AND NOT CMAKE_TOOLCHAIN_FILE )
    execute_process(COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/CMake/android/clean_all.cmake)
    set(CMAKE_TOOLCHAIN_FILE CACHE FILEPATH "Path to the toolchain file")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/android/droid_config.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/android/helper.cmake)

set(CMAKE_DROID_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE) # TODO remove PARENT_SCOPE ?

# Test not yet supported for android
unset(BUILD_TESTS CACHE) # Required for cached parameters
set(BUILD_TESTS OFF CACHE BOOL "Configures projects associated tests (<project>Test projects)")

set(SET_API_VERSION OFF PARENT_SCOPE)

# Override main CMakeLists macro
macro(fwLibExtra)
    add_push_lib()
endmacro()

# Override main CMakeLists macro
macro(fwBundleExtra)
    add_push_bundle()
endmacro()

endif()