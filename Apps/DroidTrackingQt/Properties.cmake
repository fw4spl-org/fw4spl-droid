
set( NAME DroidTrackingQt )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES
)
set( REQUIREMENTS 
    gui
    guiQt
    
    appXml
    
    dataReg
    arDataReg

    servicesReg
    launcherDroid
    droidPlugin
    vtkSimpleMesh
    visuVTK
    visuVTKQt
    visuVTKAdaptor
    visuVTKARAdaptor

    io
    ioVTK
    
    ctrlCamera
    videoTools
    visuVideoAndroid
    
    tracker
    trackerAruco
)
set( PLATFORM DROID)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DroidTrackingQtConfig)
