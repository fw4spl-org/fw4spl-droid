
set( NAME PoC09Android )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES  )
set( REQUIREMENTS
    appXml2
    servicesReg
    dataReg
    launcherDroid
    visuVTKAndroid
    vtkSimpleMesh
    io
    ioVTK
    gui
    guiAndroid
)
set( PLATFORM DROID)

bundleParam(appXml2 PARAM_LIST config PARAM_VALUES PoC09AndroidConfig)
