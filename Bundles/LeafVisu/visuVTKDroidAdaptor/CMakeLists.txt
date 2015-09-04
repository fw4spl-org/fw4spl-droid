fwLoadProperties()
fwUseForwardInclude(
    fwCom
    fwComEd
    fwData
    fwRenderVTK
    fwRuntime
    fwServices
)

find_package(VTK 
    COMPONENTS
    vtkRenderingOpenGL2
    REQUIRED
)

fwForwardInclude(
    ${VTK_INCLUDE_DIRS}
)
fwLink(
    vtkRenderingOpenGL2
)

