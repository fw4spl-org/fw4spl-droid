fwLoadProperties()

if(DroidTracking_INSTALL AND ANDROID)
    set(CMAKE_DIRECTORY ${CMAKE_DROID_SOURCE_DIR}/CMake/android)

    include("${CMAKE_DIRECTORY}/droid_setup.cmake" REQUIRED)

    set(APK_BUILD_DIR ${CMAKE_BINARY_DIR}/apk)

    file(DOWNLOAD https://owncloud.u-strasbg.fr/index.php/s/GmdjdFqZ9h7xDp7/download 
         "${CMAKE_BINARY_DIR}/Bundles/DroidTracking_0-1/liver.jsonz"
         EXPECTED_HASH SHA256=ea7295d06d05aa416c7bf64997da009df509a761d354bf2f5d28e131b1a3465e)
    configure_file("${CMAKE_DIRECTORY}/droid_builder.cmake.in" "${CMAKE_BINARY_DIR}/CMakeFiles/droid_builder.cmake" @ONLY)
    install(SCRIPT "${CMAKE_BINARY_DIR}/CMakeFiles/droid_builder.cmake")

endif()
