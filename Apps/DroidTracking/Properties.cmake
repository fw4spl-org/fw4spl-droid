
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
    ctrlCamp
    arDataReg
    visuVTKAdaptor
    visuVTKAndroid
    visuVTKARAdaptor
    visuVideoAndroid
    visuVTK
    videoTools
    io
    ioVTK
    ioAtoms
    trackerAruco
    registrationCV
    gui
    guiAndroid
    guiDroid
    maths
)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DroidTrackingConfig )
