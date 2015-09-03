##################################################
#  Create gradle build macro
##################################################

macro(gradle_build)
    configure_file("${CMAKE_DIRECTORY}/build.gradle" "${APK_INSTALL_DIR}/build.gradle")
    
    set(APK_BUILD_PATH build/outputs/apk)
    
    
    # Setup Gradle related vars
    if(UNIX)
        set(GRADLEW_EXTENSION "")
    elseif(WIN32)
        set(GRADLEW_EXTENSION ".bat")
    endif()    
        
    if(NOT EXISTS "${WORKING_DIR}/gradlew${GRADLEW_EXTENSION}")
        message("Creating gradle wrapper:")
        execute_process(
            COMMAND ${GRADLE_PRG} wrapper
            WORKING_DIRECTORY "${WORKING_DIR}"
        )
    endif()
    
    set(WRAPPER "${WORKING_DIR}/gradlew${GRADLEW_EXTENSION}") 
    
    
    message("ANDROID_APK_KEYSTORE= ${ANDROID_APK_KEYSTORE}")
    
    
    # Build the apk file
    if(CMAKE_BUILD_TYPE MATCHES Release)
        # Let gralde create the apk file 
        set (BUILD_APK_OPTIONS "assembleRelease") # --daemon --parallel
    else() 
        set (BUILD_APK_OPTIONS "assembleDebug") # --daemon --parallel
    endif()
    
    message("\nAPK ${CMAKE_BUILD_TYPE} build :")
    
    execute_process(
        COMMAND ${WRAPPER} ${BUILD_APK_OPTIONS}
        WORKING_DIRECTORY "${APK_INSTALL_DIR}"
    )
    
    set(APK_FINAL_NAME ${BASE_APP_NAME}-${CMAKE_BUILD_TYPE}.apk) 
    
    
    # Install current version on the device/emulator
    execute_process(
        COMMAND ${ADB_PRG} install -rp ${APK_BUILD_PATH}/${APK_FINAL_NAME}
        WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )
        
    message("\n\nInstall done.\n\n") 
        
endmacro(gradle_build)