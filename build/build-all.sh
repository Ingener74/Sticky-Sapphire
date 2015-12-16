#!/bin/bash

if [[ "$#" -lt 2 ]]; then
	echo "Usage: ./build-all.sh <path-to-swig-exe> <path-to-jdk>"
	exit 1
fi

cmake .. -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchains/android-cmake/android.toolchain.cmake \
	-DANDROID_ABI="armeabi-v7a with NEON" \
	-DANDROID_NATIVE_API_LEVEL=17 \
	-DSWIG_EXECUTABLE=$1 \
	-DJava_JAR_EXECUTABLE=$2/bin/jar \
	-DJava_JAVAC_EXECUTABLE=$2/bin/javac \
	-DJava_JAVADOC_EXECUTABLE=$2/bin/javadoc \
	-DJava_JAVAH_EXECUTABLE=$2/bin/javah \
	-DJava_JAVA_EXECUTABLE=$2/bin/java

make -j4