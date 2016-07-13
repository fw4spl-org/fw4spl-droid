
set( NAME DesktopTrackingQt )
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
    fwlauncher
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
    videoQt
    maths
    
    tracker
    trackerAruco
    patchMedicalData

    droidTools
    uiDroidQt
    uiData
)

bundleParam(appXml PARAM_LIST config PARAM_VALUES DesktopTrackingQtConfig)
