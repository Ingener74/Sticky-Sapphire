cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME WrenchRough)

find_package(SWIG REQUIRED)
include(UseSWIG)

set(WRAPPER_FILE ${MODULE_NAME}.i)

set_source_files_properties(${WRAPPER_FILE} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${WRAPPER_FILE} PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

set(PACKAGE_1 "org")
set(PACKAGE_2 "wrenchrougn")

set(CMAKE_SWIG_FLAGS "-c++;-package;${PACKAGE_1}.${PACKAGE_2}")
# set(CMAKE_SWIG_OUTDIR ${3RDPARTY_INSTALL}/bin/${PACKAGE_1}/${PACKAGE_2})

find_package(Java REQUIRED)
include(UseJava)

# set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/frontends/Android/Yzer/app/src/main/jniLibs/armeabi-v7a)
SWIG_ADD_MODULE(${MODULE_NAME} java ${WRAPPER_FILE})
set_target_properties(${MODULE_NAME} PROPERTIES NO_SONAME OFF)

set(SHARED_LIBS DiscardedSteel) # ${POCO_LIB} 
SWIG_LINK_LIBRARIES(${MODULE_NAME} ${SHARED_LIBS})

# set(PROJECT_DEST ${CMAKE_SOURCE_DIR}/frontends/Android/${PROJECT_NAME})

# set(ENDLESS_ELECTRON_SO_DESTINATION  ${PROJECT_DEST}/app/src/main/jniLibs/armeabi-v7a)
# set(ENDLESS_ELECTRON_JAR_DESTINATION ${PROJECT_DEST}/app/libs/)

# set(JAVA_FILES_DESTINATION ${CMAKE_SOURCE_DIR}/frontends/Android/Yzer/app/src/main/java/org/endlesselectron)

#add_custom_target(CopyJavaFiles ALL
#    COMMAND rm -rf ${JAVA_FILES_DESTINATION}
#    COMMAND mkdir -p ${JAVA_FILES_DESTINATION}
#    COMMAND rsync -a --exclude="*.jar" --exclude="*.h" --exclude="*.cxx" --exclude="*/" ${CMAKE_SWIG_OUTDIR}/* ${JAVA_FILES_DESTINATION}
#    DEPENDS ${MODULE_NAME}
#)
