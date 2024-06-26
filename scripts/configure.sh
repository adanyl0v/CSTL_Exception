#!/bin/bash

read -p "Enter the build configuration: " CONFIG

BUILD_DIR="build"
OUTPUT_DIR="bin"

# Not a necessary command, can be removed
rm -rf "./$BUILD_DIR/$CONFIG"

COMPILE_C_STANDARD=11
COMPILE_OPTIONS="-std=gnu$COMPILE_C_STANDARD"
COMPILE_OPTIONS_DEBUG="$COMPILE_OPTIONS -g3 -O0 -Wall -Waddress -Wextra -Wpedantic -Wduplicated-branches"
COMPILE_OPTIONS_RELEASE="$COMPILE_OPTIONS -DNDEBUG -g0 -O3 -Werror"
COMPILE_OPTIONS_MINSIZEREL="$COMPILE_OPTIONS -DNDEBUG -Os"
COMPILE_OPTIONS_RELWITHDEBINFO="$COMPILE_OPTIONS -g3 -O2"

cmake \
    -DCMAKE_C_STANDARD=$COMPILE_C_STANDARD \
    -DCMAKE_C_STANDARD_REQUIRED=TRUE \
    \
    -DBUILD_TESTS=FALSE \
    -DCMAKE_BUILD_TYPE=$CONFIG \
    -DBUILD_SHARED_LIBS=TRUE \
    -DCMAKE_INSTALL_PREFIX=/usr/local \
    \
    -DCMAKE_C_FLAGS="$COMPILE_OPTIONS" \
    -DCMAKE_C_FLAGS_DEBUG="$COMPILE_OPTIONS_DEBUG" \
    -DCMAKE_C_FLAGS_RELEASE="$COMPILE_OPTIONS_RELEASE" \
    -DCMAKE_C_FLAGS_MINSIZEREL="$COMPILE_OPTIONS_MINSIZEREL" \
    -DCMAKE_C_FLAGS_RELWITHDEBINFO="$COMPILE_OPTIONS_RELWITHDEBINFO" \
    \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$OUTPUT_DIR \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG=$OUTPUT_DIR/Debug \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE=$OUTPUT_DIR/Release \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL=$OUTPUT_DIR/MinSizeRel \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO=$OUTPUT_DIR/RelWithDebInfo \
    \
    -G "Unix Makefiles" \
    -B "./$BUILD_DIR/$CONFIG" \
    -S .
