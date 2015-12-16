cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME WrenchRough)

find_package(SWIG REQUIRED)
include(UseSWIG)

set(WRAPPER_FILE ${MODULE_NAME}.i)

set_source_files_properties(${WRAPPER_FILE} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${WRAPPER_FILE} PROPERTIES SWIG_FLAGS "-includeall;-nodefaultctor")

set(PACKAGE_1 "org")
set(PACKAGE_2 "wrenchrough")

set(CMAKE_SWIG_FLAGS "-c++;-package;${PACKAGE_1}.${PACKAGE_2}")

find_package(Java REQUIRED)
include(UseJava)

set(ANDROID_PROJECT_DESTINATION "${CMAKE_SOURCE_DIR}/StickySapphire/app/src/main")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ANDROID_PROJECT_DESTINATION}/jniLibs/armeabi-v7a)
SWIG_ADD_MODULE(${MODULE_NAME} java ${WRAPPER_FILE})
set_target_properties(${MODULE_NAME} PROPERTIES NO_SONAME OFF)

set(SHARED_LIBS DiscardedSteel)
SWIG_LINK_LIBRARIES(${MODULE_NAME} ${SHARED_LIBS})

include(CopyJavaFiles)
CopyJavaFiles(${MODULE_NAME} "${ANDROID_PROJECT_DESTINATION}/java/${PACKAGE_1}/${PACKAGE_2}")

