
set( NAME uiDroidQt )
set( VERSION 0.1 )
set( TYPE BUNDLE )
set( DEPENDENCIES 
        fwCore
        fwData
        fwDataTools
        fwRuntime
        fwServices
        fwTools
        fwGui
        fwGuiQt 
        fwCom
        gui 
)
set( REQUIREMENTS  )

if(ANDROID)
    set( PLATFORM DROID )
endif()

