##################################################
#  Create ant build macro
##################################################

macro(ant_build)
    
    # Build the apk file
    if(CMAKE_BUILD_TYPE MATCHES Release)
        # Let Ant create the unsigned apk file
        message("\nAPK Release build :\n")
        execute_process(
            COMMAND ${ANT_PRG} release
            WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )

        # Sign the apk file
        execute_process(
            COMMAND ${JARSIGNER_PRG} -verbose -keystore ${ANDROID_APK_SIGNER_KEYSTORE} bin/${BASE_APP_NAME}-unsigned.apk ${ANDROID_APK_SIGNER_ALIAS}
            WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )

        # Align the apk file
        execute_process(
            COMMAND ${ZIPALIGN_PRG} -v -f 4 bin/${BASE_APP_NAME}-unsigned.apk bin/${BASE_APP_NAME}.apk
            WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )

        #Install current version on the device/emulator
        execute_process(
            COMMAND ${ADB_PRG} install -r bin/${BASE_APP_NAME}.apk
            WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )

    else()
         message("\nAPK Debug build :\n")
        
        # In case of debug build, do also copy gdbserver
        # add_custom_command(TARGET ${BASE_APP_NAME}
       #      POST_BUILD
       #      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_GDBSERVER} "${APK_INSTALL_DIR}/libs/${ARM_TARGET}"
       #  )
       
        # Let Ant create the unsigned apk file
        execute_process(
            COMMAND ${ANT_PRG} debug
            WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )
        
        #Install current version on the device/emulator
        execute_process(
            COMMAND ${ADB_PRG} install -r bin/${BASE_APP_NAME}-debug.apk
            WORKING_DIRECTORY "${APK_INSTALL_DIR}"
        )
        
    endif()
    
endmacro(ant_build)