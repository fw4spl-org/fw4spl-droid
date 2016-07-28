
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
    tracker
    trackerAruco
    gui
    guiAndroid
    guiDroid
    maths
)
set(JAVA_PACKAGES ndkgui)
bundleParam(appXml2 PARAM_LIST config PARAM_VALUES DroidTrackingConfig )
