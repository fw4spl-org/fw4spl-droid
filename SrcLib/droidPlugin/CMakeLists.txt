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
    ${EXTERNAL_LIBRARIES}/include/QtGui/${Qt5_VERSION}/
    ${EXTERNAL_LIBRARIES}/include/QtGui/${Qt5_VERSION}/QtGui
    ${EXTERNAL_LIBRARIES}/include/QtCore/${Qt5_VERSION}/
    ${EXTERNAL_LIBRARIES}/include/QtCore/${Qt5_VERSION}/QtCore
    ${EXTERNAL_LIBRARIES}/include/QtPlatformSupport/${Qt5_VERSION}/
)

fwLink(
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${EXTERNAL_LIBRARIES}/lib/libQt5PlatformSupport.a
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
    LIBRARY DESTINATION ${EXTERNAL_LIBRARIES}/plugins/platforms/
)
