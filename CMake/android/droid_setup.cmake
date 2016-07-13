
##################################################
#  Variables usefull for apk buld
##############################################
set(LIB_PREFIX "lib")

##################################################
#  Macro
##################################################

# Setup dependencies for apk build
macro(setup_dependencies)
    unset(LIBS)
    unset(DEPENDS_OUTPUT)
    
    # Find programs android, adb, ant, jarsigner and zipalign
    if(CMAKE_HOST_WIN32)
        set(NDK_DEPENDS_PATH "${ANDROID_NDK}/prebuilt/windows-x86_64/bin")
    else()
        set(NDK_DEPENDS_PATH ${ANDROID_NDK})
    endif()
    find_program(NDK_DEPENDS_PRG ndk-depends NAMES ndk-depends PATHS ${NDK_DEPENDS_PATH} NO_CMAKE_FIND_ROOT_PATH )
    if (NOT NDK_DEPENDS_PRG)
        message(FATAL_ERROR "ndk-depends command is not found.")
    endif()
    
    file(GLOB_RECURSE  DEPENDENCIES ${WORKING_DIR}/Bundles/* ${WORKING_DIR}/lib/*)
    foreach(CURRENT_FILE ${DEPENDENCIES})
        get_filename_component(EXTENSION ${CURRENT_FILE} EXT)
        if("${EXTENSION}" STREQUAL ".so")
            execute_process(
                COMMAND ${NDK_DEPENDS_PRG} --print-paths -L ${EXTERNAL_LIBRARIES}/lib -L ${CMAKE_INSTALL_PREFIX}/lib ${CURRENT_FILE}
                OUTPUT_VARIABLE DEPENDS_OUTPUT
            ) 
        endif()
        if(DEPENDS_OUTPUT)
            string(REPLACE "\n" ";" DEPENDS_LINE "${DEPENDS_OUTPUT}")
            
            string(LENGTH "${DEPENDS_LINE}" LINE_LENGHT)
            math( EXPR FINAL_LENGTH "${LINE_LENGHT} - 1 " )
            string(SUBSTRING "${DEPENDS_LINE}" 0 ${FINAL_LENGTH} DEPENDS_LINE)

            foreach(CURRENT_DEPS ${DEPENDS_LINE})
                string(LENGTH "${CURRENT_DEPS}" DEP_LENGHT)
                string(FIND "${CURRENT_DEPS}" "->" ARROW_POSITION)
                math( EXPR BEGIN_POSTION "${ARROW_POSITION} + 3 " )
                math( EXPR FINAL_LENGTH "${DEP_LENGHT} - ${BEGIN_POSTION} " )
                string(SUBSTRING "${CURRENT_DEPS}" ${BEGIN_POSTION} ${FINAL_LENGTH} DEPS_PATH)
                string(FIND "${DEPS_PATH}" "$" TEST_SYSTEM)
                string(FIND "${DEPS_PATH}" "!!" TEST_EXT)

                if(${TEST_SYSTEM} EQUAL -1)
                    if(NOT ${TEST_EXT} EQUAL -1)
                        math( EXPR FINAL_POSTION "${ARROW_POSITION} - 1 " )
                        string(SUBSTRING "${CURRENT_DEPS}" 0 ${FINAL_POSTION} EXT_PATH)
                    else()
                        list(APPEND LIBS "${DEPS_PATH}")
                    endif()
                endif()
            endforeach()
            
        endif()
    endforeach()
    if(LIBS)
        list(REMOVE_DUPLICATES LIBS)
    else()
        message( FATAL_ERROR "No libraries found !")
    endif()

    list(APPEND LIBS "${WORKING_DIR}/lib/lib${BASE_APP_LIB_NAME}.so")

    string(LENGTH "${WORKING_DIR}" WORKING_DIR_LENGTH)
    string(LENGTH "${LIB_PREFIX}" LIB_PREFIX_LENGTH)
    
    #  Set files for apk build
    setup_bundles_and_shared()
    setup_java()
    setup_qt()
    
endmacro()
  
# Search and set fw4spl bundles and shared
macro(setup_bundles_and_shared )
    unset(LIBS_ASSETS)
    unset(ASSETS_FILE)
    
    file(GLOB_RECURSE  FILES_LIST ${WORKING_DIR}/Bundles/* )
    foreach(CURRENT_FILE ${FILES_LIST})
        get_filename_component(EXTENSION ${CURRENT_FILE} EXT)
        get_filename_component(LIB_NAME ${CURRENT_FILE} NAME)
        get_filename_component(LIB_NAME_WE ${CURRENT_FILE} NAME_WE)

        get_filename_component(DIR_PATH ${CURRENT_FILE} DIRECTORY)
        get_filename_component(DIR_NAME ${DIR_PATH} NAME)

        string(LENGTH ${CURRENT_FILE} CURRENT_LENGTH)
        math( EXPR FINAL_LENGTH "${CURRENT_LENGTH} - ${WORKING_DIR_LENGTH}" ) 
        string(SUBSTRING ${CURRENT_FILE} ${WORKING_DIR_LENGTH} ${FINAL_LENGTH} SUB_DIR)
    
        if(NOT "${EXTENSION}" STREQUAL ".DS_Store") # osx problem
            if(NOT "${EXTENSION}" STREQUAL ".so" )
                list(APPEND LIBS_ASSETS ${SUB_DIR})
                
                string(LENGTH ${SUB_DIR} SUB_LENGTH)
                math( EXPR SUB_LENGTH "${SUB_LENGTH} - 1" )
                string(SUBSTRING ${SUB_DIR} 1 ${SUB_LENGTH} FINAL_DIR)
                list(APPEND ASSETS_FILE ${FINAL_DIR})
    
            endif()
        endif()
    endforeach()
    
    file(GLOB_RECURSE  CURRENT_DIR ${WORKING_DIR}/share/* )
    foreach(CURRENT_FILE ${CURRENT_DIR})
        get_filename_component(EXTENSION ${CURRENT_FILE} EXT)
        get_filename_component(LIB_NAME ${CURRENT_FILE} NAME)
        get_filename_component(LIB_NAME_WE ${CURRENT_FILE} NAME_WE)

        get_filename_component(DIR_PATH ${CURRENT_FILE} DIRECTORY)
        get_filename_component(DIR_NAME ${DIR_PATH} NAME)

        string(LENGTH ${CURRENT_FILE} CURRENT_LENGTH)
        math( EXPR FINAL_LENGTH "${CURRENT_LENGTH} - ${WORKING_DIR_LENGTH}" )
        string(SUBSTRING ${CURRENT_FILE} ${WORKING_DIR_LENGTH} ${FINAL_LENGTH} SUB_DIR)

        if(NOT "${EXTENSION}" STREQUAL ".DS_Store") # osx problem
            if("${EXTENSION}" STREQUAL ".so")
                list(APPEND LIBS ${CURRENT_FILE})
            elseif(EXTENSION)
                list(APPEND LIBS_ASSETS ${SUB_DIR})

                string(LENGTH ${SUB_DIR} SUB_LENGTH)
                math( EXPR SUB_LENGTH "${SUB_LENGTH} - 1" )
                string(SUBSTRING ${SUB_DIR} 1 ${SUB_LENGTH} FINAL_DIR)
                list(APPEND ASSETS_FILE ${FINAL_DIR})
                
            endif()
        endif()
    endforeach()
endmacro()

# Search and set jar dependencies
macro(setup_java )
    unset(FWJAVA_FILES)
    unset(JAR_LIBS)
    unset(JAVA_FILES)
    unset(LIBS_TO_LOAD)
    
    set(DIR_LIST ${SOURCE_DIR} ${ADDITIONAL_PROJECTS})
    foreach(CURRENT_DIR ${DIR_LIST})
        file(GLOB_RECURSE  FILES_LIST FOLLOW_SYMLINKS ${CURRENT_DIR}/*.java)
        foreach(CURRENT_FILE ${FILES_LIST})
            
            string(FIND ${CURRENT_FILE} "/bindings" DIR_POS)
            string(SUBSTRING ${CURRENT_FILE} 0 ${DIR_POS} FINAL_DIR)
            get_filename_component(DIR_NAME ${FINAL_DIR} NAME)
            string(FIND "${PROJECTS_TO_INSTALL}" ${DIR_NAME} PROJECT_TEST)
            
            if(NOT ${PROJECT_TEST} EQUAL -1)
                list(APPEND FWJAVA_FILES ${CURRENT_FILE})
            endif()
        endforeach()
    endforeach()

    string(LENGTH "${EXTERNAL_LIBRARIES}/" ROOT_LENGTH)
    set(JAR_DIR  "${EXTERNAL_LIBRARIES}/jar")

    file(GLOB_RECURSE JAR_FILES  "${JAR_DIR}/*")

    foreach(CURRENT_FILE ${JAR_FILES})
        get_filename_component(EXTENSION ${CURRENT_FILE} EXT)
        get_filename_component(FILE_NAME ${CURRENT_FILE} NAME_WE)
    
        string(FIND "${JAR_REQUIREMENTS}" ${FILE_NAME} JAR_TEST)
        string(FIND ${FILE_NAME} "bundled" BUNDLED_TEST)
        
        if( NOT ${JAR_TEST} EQUAL -1 AND NOT ${BUNDLED_TEST} EQUAL -1 )
            list(APPEND JAR_LIBS ${CURRENT_FILE})
        endif()

    endforeach()

    if(JAVA_PACKAGES)
        set(JAVA_DIR  "${EXTERNAL_LIBRARIES}/src/com")
        file(GLOB_RECURSE JAVA_FILES_LIST  "${JAVA_DIR}/*")
       
        foreach(CURRENT_FILE ${JAVA_FILES_LIST})
            string(FIND ${CURRENT_FILE} "${JAVA_PACKAGES}" PACKAGE_TEST)
            if(NOT ${PACKAGE_TEST} EQUAL -1 )
                list(APPEND JAVA_FILES ${CURRENT_FILE})
            endif()
        endforeach()
    
        string(FIND ${JAVA_PACKAGES} "ndkgui" GUI_TEST)
        message(" JAVA_PACKAGES = ${JAVA_PACKAGES}")
        if(NOT GUI_TEST EQUAL -1)
            list(APPEND LIBS_TO_LOAD "System.loadLibrary(\"JUIHelper\");")
        endif()
    endif()
    
endmacro()

# Search and set QT dependencies
macro(setup_qt )
    list(APPEND LIBS "${EXTERNAL_LIBRARIES}/lib/libfreetype.so")
    list(APPEND LIBS "${EXTERNAL_LIBRARIES}/lib/libQt5Multimedia.so")
    list(APPEND LIBS "${EXTERNAL_LIBRARIES}/lib/libQt5Network.so")
    
    string(LENGTH "${EXTERNAL_LIBRARIES}/" QT_LENGTH)
    file(GLOB QT_DIRS "${EXTERNAL_LIBRARIES}/plugins/*")
    foreach(CURRENT_DIR ${QT_DIRS})
    
        get_filename_component(QT_NAME ${CURRENT_DIR} NAME)
        string(FIND "${QT_REQUIREMENTS}" ${QT_NAME} QT_TEST)
        if( NOT ${QT_TEST} EQUAL -1 AND NOT "${QT_NAME}" STREQUAL "Qt")
                
            file(GLOB_RECURSE QT_FILES  "${CURRENT_DIR}/*")
            foreach(CURRENT_FILE ${QT_FILES})
                get_filename_component(EXTENSION ${CURRENT_FILE} EXT)
                get_filename_component(FILE_NAME ${CURRENT_FILE} NAME)
            
                 string(LENGTH ${CURRENT_FILE} CURRENT_LENGTH)
                 math( EXPR FINAL_LENGTH "${CURRENT_LENGTH} - ${QT_LENGTH}" )
                 string(SUBSTRING ${CURRENT_FILE} ${QT_LENGTH} ${FINAL_LENGTH} SUB_DIR)

                if(NOT "${EXTENSION}" STREQUAL ".DS_Store" ) # osx problem
                    if("${EXTENSION}" STREQUAL ".so")
                        list(APPEND LIBS ${CURRENT_FILE})
                    endif()
                    list(APPEND LIBS_ASSETS ${SUB_DIR})
                    list(APPEND ASSETS_FILE ${SUB_DIR})
                endif()
            endforeach()
        endif()
     endforeach()
endmacro()
    
