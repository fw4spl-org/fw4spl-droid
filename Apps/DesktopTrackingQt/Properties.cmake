
set( NAME DesktopTrackingQt )
set( VERSION 0.1 )
set( TYPE APP )
set( DEPENDENCIES
)
set( REQUIREMENTS 
    gui
    guiQt
    
    activities
    appXml2
    
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
    
    tracker
    trackerAruco
    patchMedicalData

    droidTools
    uiDroidQt
    uiData
    uiIO
    uiLogo
)

bundleParam(appXml2 PARAM_LIST config PARAM_VALUES DesktopTrackingQtConfig)
