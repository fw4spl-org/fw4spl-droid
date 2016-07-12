fwLoadProperties()

add_definitions("-DQT_NO_KEYWORDS")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(GLM REQUIRED)

fwForwardInclude(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIR}
)

fwLink(
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)

set_target_properties(${FWPROJECT_NAME} PROPERTIES AUTOMOC TRUE)
