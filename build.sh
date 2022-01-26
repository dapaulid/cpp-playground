#!/bin/bash -e

SRC_FILE=$1
OUTPUT_DIR="build"

# check if file specified
if [ -z $SRC_FILE ]
then
    echo "error: please input file (*.cpp)"
	exit 1
fi

# check if file exists
if [ ! -f $SRC_FILE ]; then
    echo "error: input file not found: $SRC_FILE"
	exit 1
fi

EXEC_NAME=$(basename -- ${SRC_FILE%.*})
EXEC_FILE="$OUTPUT_DIR/$EXEC_NAME"

emcmake cmake -S . -B build -DMY_SRC_FILE=$SRC_FILE -DMY_EXEC_NAME=$EXEC_NAME #-DCMAKE_EXECUTABLE_SUFFIX=.html
emmake make -C build
#libs/emsdk/upstream/emscripten/emcmake cmake --build build --config Release