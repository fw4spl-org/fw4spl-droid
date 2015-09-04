fwLoadProperties()

if(DroidRender_INSTALL AND ANDROID)
    set(CMAKE_DIRECTORY ${CMAKE_DROID_SOURCE_DIR}/CMake/android)

    include("${CMAKE_DIRECTORY}/droid_setup.cmake" REQUIRED)

    set(APK_BUILD_DIR ${CMAKE_BINARY_DIR}/apk)

    configure_file("${CMAKE_DIRECTORY}/droid_builder.cmake.in" "${CMAKE_BINARY_DIR}/CMakeFiles/droid_builder.cmake" @ONLY)
    install(SCRIPT "${CMAKE_BINARY_DIR}/CMakeFiles/droid_builder.cmake")

endif()
