#!/bin/bash -e

source common.sh

case $PLATFORM in
	"native")
		cmake -S . -B build/$PLATFORM -DPLATFORM=$PLATFORM
		cmake --build build/$PLATFORM
		;;

	"web")
		emcmake cmake -S . -B build/$PLATFORM -DPLATFORM=$PLATFORM
		emmake make -C build/$PLATFORM #VERBOSE=1
		;;

	*)
		echo "error: unsupported platform: $PLATFORM"
		exit 1
		;;
esac


