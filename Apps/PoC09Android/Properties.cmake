
set( NAME PoC09Android )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES  )
set( REQUIREMENTS
    appXml
    servicesReg
    dataReg
    launcher
    visu
    visuVTKAndroid
    vtkSimpleMesh
    io
    ioVTK
)
set( PLATFORM DROID)

bundle_param(appXml PARAM_LIST config PARAM_VALUES PoC09AndroidConfig)
