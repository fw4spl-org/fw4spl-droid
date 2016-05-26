fwLoadProperties()

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

fwInclude(
    ${VTK_INCLUDE_DIRS}
)

fwLink(
    vtkRenderingOpenGL2
    vtkInteractionStyle
)
