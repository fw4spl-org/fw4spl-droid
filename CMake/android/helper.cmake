macro(add_push_lib)
    if(EXISTS "${PRJ_SOURCE_DIR}/rc")
        add_custom_target(${FWPROJECT_NAME}_push
            # COMMAND ${ADB_PRG} push ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIR}/lib${FWPROJECT_NAME}.so /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/lib${FWPROJECT_NAME}.so
            # COMMAND ${ADB_PRG} shell "su -c 'rm -rf /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}.so'"
            # COMMAND ${ADB_PRG} shell "su -c 'mv -v /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/lib${FWPROJECT_NAME}.so /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}.so'"
            # COMMAND ${ADB_PRG} shell "su -c 'chmod 755 /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}.so'"
        
            COMMAND ${ADB_PRG} push ${CMAKE_BINARY_DIR}/share/${FWPROJECT_NAME}_${DASH_VERSION} /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}
            COMMAND ${ADB_PRG} shell "su -c 'mv -v /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/* /data/data/${PACKAGE_DOT}/share/${FWPROJECT_NAME}_${DASH_VERSION}/*'"
            
            COMMAND ${ADB_PRG} shell "su -c 'rm -r /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}'"
        )
    else()
        add_custom_target(${FWPROJECT_NAME}_push
            # COMMAND ${ADB_PRG} push ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIR}/lib${FWPROJECT_NAME}.so /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/lib${FWPROJECT_NAME}.so
            # COMMAND ${ADB_PRG} shell "su -c 'rm -rf /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}.so'"
            # COMMAND ${ADB_PRG} shell "su -c 'mv -v /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/lib${FWPROJECT_NAME}.so /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}.so'"
            # COMMAND ${ADB_PRG} shell "su -c 'chmod 755 /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}.so'"
            #
            # COMMAND ${ADB_PRG} shell "su -c 'rm -r /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}'"
        )
    endif()
endmacro(add_push_lib)

macro(add_push_bundle)
    file(GLOB_RECURSE BUNDLE_FILES  "${BUNDLE_DIR}/*")
    set(BUNDLE_RC "su -c '")
    foreach(CURRENT_FILE ${BUNDLE_FILES})
        get_filename_component(EXTENSION ${CURRENT_FILE} EXT)
        if( NOT ${EXTENSION} STREQUAL ".so" AND NOT ${EXTENSION} STREQUAL ".DS_Store" )
            get_filename_component(FILENAME ${CURRENT_FILE} NAME)
            
            string(LENGTH ${CURRENT_FILE} CURRENT_LENGTH)
            string(LENGTH ${FWPROJECT_NAME}_${DASH_VERSION} PRJ_NAME_LENGTH)
            
            
            string(FIND ${CURRENT_FILE} "${FWPROJECT_NAME}_${DASH_VERSION}" PRJ_NAME_POS REVERSE)
            MATH( EXPR PRJ_NAME_POS "${PRJ_NAME_POS} + ${PRJ_NAME_LENGTH} + 1" )
             
            MATH( EXPR FINAL_LENGTH "${CURRENT_LENGTH} - ${PRJ_NAME_POS}" )
            string(SUBSTRING ${CURRENT_FILE} ${PRJ_NAME_POS} ${FINAL_LENGTH} SUB_DIR )
            
            set(BUNDLE_RC "${BUNDLE_RC}mv -v /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/${SUB_DIR} /data/data/${PACKAGE_DOT}/Bundles/${FWPROJECT_NAME}_${DASH_VERSION}/${SUB_DIR};")
        endif()
        
    endforeach()
    
    set(BUNDLE_RC "${BUNDLE_RC} '")
    add_custom_target(${FWPROJECT_NAME}_push
        COMMAND ${ADB_PRG} push ${BUNDLE_DIR} /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}
        # COMMAND ${ADB_PRG} shell "su -c 'rm -rf /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}_${DASH_VERSION}.so'"
        # COMMAND ${ADB_PRG} shell "su -c 'mv -v /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}/lib${FWPROJECT_NAME}_${DASH_VERSION}.so /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}_${DASH_VERSION}.so'"
        # COMMAND ${ADB_PRG} shell "su -c 'chmod 755 /data/data/${PACKAGE_DOT}/lib/lib${FWPROJECT_NAME}_${DASH_VERSION}.so'"
        
        COMMAND ${ADB_PRG} shell ${BUNDLE_RC}
        
        COMMAND ${ADB_PRG} shell "su -c 'rm -r /sdcard/fw4spl_tmp/${FWPROJECT_NAME}_${DASH_VERSION}'"
    )    
endmacro(add_push_bundle)