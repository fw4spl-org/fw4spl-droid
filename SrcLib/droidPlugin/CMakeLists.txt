fwLoadProperties()
add_definitions("-DQT_NO_KEYWORDS")
add_definitions(-DPLUGIN_TYPE=platforms)
add_definitions(-DPLUGIN_CLASS_NAME=QMinimalEglIntegrationPlugin)
add_definitions(-DQT_SHARED)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Freetype  REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")

fwInclude(${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${EXTERNAL_LIBRARIES}/include/QtGui/5.5.1/
    ${EXTERNAL_LIBRARIES}/include/QtGui/5.5.1/QtGui
    ${EXTERNAL_LIBRARIES}/include/QtCore/5.5.1/
    ${EXTERNAL_LIBRARIES}/include/QtCore/5.5.1/QtCore
    ${EXTERNAL_LIBRARIES}/include/QtPlatformSupport/5.5.1/
)

fwLink(
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    /Users/fchamp/Dev/CMake/v0.10/Deps-droid/Install_debug/lib/libQt5PlatformSupport.a
    android
    log
    EGL
    GLESv2
    z
    stdc++
)

set_target_properties(${FWPROJECT_NAME} PROPERTIES 
    AUTOMOC TRUE
    OUTPUT_NAME "${FWPROJECT_NAME}"
)

install(TARGETS ${FWPROJECT_NAME}
    LIBRARY DESTINATION /Users/fchamp/Dev/CMake/v0.10/Deps-droid/Install_debug/plugins/platforms/
)
