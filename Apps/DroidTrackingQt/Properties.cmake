
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

    trackerAruco
    registrationCV
    patchMedicalData

    droidTools
    uiDroidQt
)
set( PLATFORM DROID)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DroidTrackingQtConfig)
