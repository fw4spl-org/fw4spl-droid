
set( NAME DroidTrackingQt )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES
)
set( REQUIREMENTS
    gui
    guiQt

    appXml2

    dataReg
    arDataReg

    ctrlCamp

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
    ioAtoms

    ctrlCamera
    videoTools
    visuVideoAndroid
    maths

    tracker
    trackerAruco
    patchMedicalData

    droidTools
    uiDroidQt
)
set( PLATFORM DROID)

bundleParam(appXml2 PARAM_LIST config PARAM_VALUES DroidTrackingQtConfig)
