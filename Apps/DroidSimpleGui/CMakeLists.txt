fwLoadProperties()

set(JAVA_PACKAGES ndkgui)

if(DroidSimpleGui_INSTALL AND ANDROID)

    set(CMAKE_DIRECTORY ${CMAKE_DROID_SOURCE_DIR}/CMake/android)

    include("${CMAKE_DIRECTORY}/droid_setup.cmake" REQUIRED)

    set(APK_BUILD_DIR ${CMAKE_BINARY_DIR}/apk)

    # make sure the paths contain no '\', because configure_file would produce a bad droid_builder.cmake, which would then mess up the install process SILENTLY on some platforms 
    file(TO_CMAKE_PATH ${ANDROID_APK_KEYSTORE} ANDROID_APK_KEYSTORE)
    
    configure_file("${CMAKE_DIRECTORY}/droid_builder.cmake.in" "${CMAKE_BINARY_DIR}/CMakeFiles/droid_builder.cmake" @ONLY)
    install(SCRIPT "${CMAKE_BINARY_DIR}/CMakeFiles/droid_builder.cmake")

endif()
