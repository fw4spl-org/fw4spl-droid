
set( NAME DroidTracking )
set( VERSION 0.1 )
set( TYPE APP )
set( PLATFORM DROID )
set( DEPENDENCIES  )
set( REQUIREMENTS
    appXml
    servicesReg
    dataReg
    extDataReg
    launcherDroid
    ctrlCamera
    arDataReg
    visuVTKAdaptor
    visuVTKAndroid
    visuVTKARAdaptor
    visuVideoAndroid
    visu
    visuVTK
    videoTools
    vtkSimpleMesh
    io
    ioVTK
    tracker
    trackerAruco
    gui
    guiAndroid
)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DroidTrackingConfig )
