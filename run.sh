#!/usr/bin/env bash
SRC_FILE=$1
OUTPUT_DIR="build"

if [ -z "$SRC_FILE" ]
then
    echo "error: please input file (*.cpp)"
	exit 1
fi

EXEC_NAME=$(basename -- ${SRC_FILE%.*})
EXEC_FILE="$OUTPUT_DIR/$EXEC_NAME"

mkdir -p $OUTPUT_DIR
g++ $SRC_FILE -std=c++11 -isystem libs/benchmark/include -Llibs/benchmark/build/src -lbenchmark -lpthread -o $EXEC_FILE && ./$EXEC_FILE
