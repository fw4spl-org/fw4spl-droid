
set( NAME DroidSimpleGui )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES  )
set( REQUIREMENTS
    appXml
    servicesReg
    dataReg
    launcherDroid
    visu
    visuVTKAndroid
    visuVTKAdaptor
    vtkSimpleMesh
    guiDroid
    io
    ioVTK
)
set( PLATFORM DROID)

bundle_param(appXml PARAM_LIST config PARAM_VALUES DroidSimpleGuiConfig)
