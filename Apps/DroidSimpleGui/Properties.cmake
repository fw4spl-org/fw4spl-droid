
set( NAME DroidSimpleGui )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES  )
set( REQUIREMENTS
    appXml
    servicesReg
    dataReg
    launcherDroid
    visuVTK
    visuVTKAndroid
    visuVTKAdaptor
    vtkSimpleMesh
    guiDroid
    io
    ioVTK
    gui
    guiAndroid
)
set( PLATFORM DROID)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DroidSimpleGuiConfig)
