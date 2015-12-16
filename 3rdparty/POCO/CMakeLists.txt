cmake_minimum_required(VERSION 3.0)

set(EXT_POCO ext_POCO)

ExternalProject_Add(
    ${EXT_POCO}
    URL                 http://pocoproject.org/releases/poco-1.6.1/poco-1.6.1-all.tar.gz
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${3RDPARTY_INSTALL}
                        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                        -DENABLE_DATA=OFF
                        -DENABLE_DATA_SQLITE=OFF
                        -DENABLE_DATA_ODBC=OFF
                        -DENABLE_DATA_MYSQL=OFF
                        -DENABLE_APACHECONNECTOR=OFF
                        -DENABLE_POCODOC=OFF
                        -DENABLE_PDF=OFF
                        -DENABLE_PAGECOMPILER=OFF
                        -DENABLE_PAGECOMPILER_FILE2PAGE=OFF
                        -DENABLE_ZIP=OFF
                        -DENABLE_XML=OFF
                        -DENABLE_MONGODB=OFF
                        -DENABLE_TESTS=OFF
                        -DENABLE_CRYPTO=OFF
                        -DENABLE_JSON=OFF
                        -DENABLE_NET=OFF
                        -DENABLE_NETSSL=OFF
                        -DENABLE_UTIL=OFF
                        -DPOCO_STATIC=ON
                        -DANDROID_ABI=${ANDROID_ABI}
                        -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}
)

unset(POCO_LIB)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(POCO_LIB
        PocoFoundationd
        PARENT_SCOPE
    )
else()
    set(POCO_LIB
        PocoFoundation
        PARENT_SCOPE
    )
endif()


