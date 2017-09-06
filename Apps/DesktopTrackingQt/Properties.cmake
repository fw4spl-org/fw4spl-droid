
set( NAME DesktopTrackingQt )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES
)
set( REQUIREMENTS
    gui
    guiQt

    activities
    appXml

    dataReg
    arDataReg

    ctrlCamp

    servicesReg
    fwlauncher
    vtkSimpleMesh
    visuVTK
    visuVTKQt
    visuVTKAdaptor
    visuVTKARAdaptor

    io
    ioVTK
    ioAtoms
    ioActivity

    ctrlCamera
    videoTools
    videoQt
    maths

    trackerAruco
    registrationARL
    patchMedicalData

    droidTools
    uiDroidQt
    uiData
    uiIO
    uiLogo
)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DesktopTrackingQtConfig)
