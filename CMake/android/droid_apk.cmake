##################################################
#  Create APK macro
##################################################

macro(create_apk)
    
    if( ${APK_BUILD_TOOL} STREQUAL "ant" )
        include(${CMAKE_DIRECTORY}/ant_build.cmake REQUIRED)
    elseif( ${APK_BUILD_TOOL} STREQUAL "gradle" )
        include(${CMAKE_DIRECTORY}/gradle_build.cmake REQUIRED)
    endif()

    set(ANDROID_APK_THEME "android:theme=\"@android:style/Theme.NoTitleBar.Fullscreen\"")
        
    execute_process(
        COMMAND ${ANDROID_PRG} update project -t android-${ANDROID_API_LEVEL} --name "${BASE_APP_NAME}" --path "${APK_INSTALL_DIR}"
    )

    message("Copying files to apk build directory:")
    
    #JAR files:
    message("- Copying JAR libraries ...")
    foreach(JAR_FILE ${JAR_LIBS})
        execute_process(
             COMMAND ${CMAKE_COMMAND} -E copy_if_different "${JAR_FILE}" "${APK_INSTALL_DIR}/libs"
         )
    endforeach()

    ##################################################
    #  Copy java files
    ##################################################
    # copy Java file which is responsible for loading in the required shared librarie
    message("- Copying Java files ...")
    
    foreach(FWJAVA_FILE ${FWJAVA_FILES})
        get_filename_component(CURRENT_NAME ${FWJAVA_FILE} NAME)
        configure_file(${FWJAVA_FILE}   "${APK_INSTALL_DIR}/src/${ANDROID_APK_TOP_LEVEL_DOMAIN}/${ANDROID_APK_DOMAIN}/${ANDROID_APK_SUBDOMAIN}/${CURRENT_NAME}")
    endforeach()
    

    foreach(JAVA_FILE ${JAVA_FILES})
        string(FIND ${JAVA_FILE} "com" PACKAGE_POS)
        string(LENGTH ${JAVA_FILE} CURRENT_LENGTH)
        MATH( EXPR FINAL_LENGTH "${CURRENT_LENGTH} - ${PACKAGE_POS}" )
        string(SUBSTRING ${JAVA_FILE} ${PACKAGE_POS} ${FINAL_LENGTH} SUB_DIR)
        set(JAVA_DEST ${SUB_DIR})
        
        execute_process(
             COMMAND ${CMAKE_COMMAND} -E copy_if_different "${JAVA_FILE}" "${APK_INSTALL_DIR}/src/${JAVA_DEST}"
         )
    endforeach()
    
    ##################################################
    #  Copy libs
    ##################################################
    message("- Copying libraries ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory "${APK_INSTALL_DIR}/libs/${ARM_TARGET}"
    )
    
    # Copy the used shared libraries
    foreach(value ${LIBS})
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${value} "${APK_INSTALL_DIR}/libs/${ARM_TARGET}"
        )
    endforeach()
    
    ##################################################
    #  Copy assets
    ##################################################
    message("- Copying assets ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory "${APK_INSTALL_DIR}/assets"
    )

    foreach(value ${LIBS_ASSETS})
        get_filename_component(file_name ${value} NAME)
        get_filename_component(dir_src ${value} DIRECTORY)
        get_filename_component(dir_name ${dir_src} NAME)
        
        if(EXISTS "${CMAKE_BINARY_DIR}/${value}" )
           set(src ${CMAKE_BINARY_DIR}/${value})
        else()
           set(src ${EXTERNAL_LIBRARIES}/${value})
        endif()

        set(dest "${APK_INSTALL_DIR}/assets/${value}")
        #message(" src = ${src}")
        execute_process(
             COMMAND ${CMAKE_COMMAND} -E copy_if_different ${src} ${dest}
         )
         
    endforeach()
    
    # Move app profile in assets base directory
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${APK_INSTALL_DIR}/assets/Bundles/${BASE_APP_NAME}/profile.xml ${APK_INSTALL_DIR}/assets/profile.xml
    )

    # Copy gdbserver to lib directory if this is a Debug version
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        message("- Copying gdbserver ...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ANDROID_NDK}/prebuilt/android-arm/gdbserver/gdbserver" "${APK_INSTALL_DIR}/libs/${ARM_TARGET}/libgdbserver.so"
        )
    endif()


    # Uninstall previous version from the device/emulator (else we may get e.g. signature conflicts)
    message("Uninstall previous apk")
    execute_process(
        COMMAND ${ADB_PRG} uninstall "${ANDROID_APK_PACKAGE}"
    )

    # Build the apk file
    if( ${APK_BUILD_TOOL} STREQUAL "ant" )
        ant_build()
    elseif( ${APK_BUILD_TOOL} STREQUAL "gradle" )
        gradle_build()
    endif()

    #Start the application
    # execute_process(
        # COMMAND ${ADB_PRG} shell am start -n ${ANDROID_APK_PACKAGE}/.LauncherActivity
        # WORKING_DIRECTORY "${APK_INSTALL_DIR}"
    # )
    
endmacro(create_apk)
