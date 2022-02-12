#!/bin/bash -e

source common.sh

case $PLATFORM in
	"native")
		cmake -S . -B build/$PLATFORM -DPLATFORM=$PLATFORM -DCMAKE_BUILD_TYPE=Debug   # TODO
		cmake --build build/$PLATFORM
		;;

	"web")
		emcmake cmake -S . -B build/$PLATFORM -DPLATFORM=$PLATFORM -DCMAKE_BUILD_TYPE=Debug   # TODO
		emmake make -C build/$PLATFORM #VERBOSE=1
		;;

	*)
		echo "error: unsupported platform: $PLATFORM"
		exit 1
		;;
esac


