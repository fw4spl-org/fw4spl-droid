
set( NAME DroidSimpleQt )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES
)
set( REQUIREMENTS 
    gui
    guiQt
    
    appXml
    
    dataReg

    servicesReg
    launcherDroid
    droidPlugin
    vtkSimpleMesh
    visuVTK
    visuVTKQt
    visuVTKAdaptor

    io
    ioVTK
)
set( PLATFORM DROID)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DroidSimpleQtConfig)
