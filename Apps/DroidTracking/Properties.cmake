
set( NAME DroidTracking )
set( VERSION 0.1 )
set( TYPE APP )
set( PLATFORM DROID )
set( DEPENDENCIES  )
set( REQUIREMENTS
    appXml2
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
    registrationARL
    gui
    guiAndroid
    guiDroid
    maths
)

bundleParam(appXml2 PARAM_LIST config PARAM_VALUES DroidTrackingConfig )
