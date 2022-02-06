#!/bin/bash -e

platform=$1

if [[ ! $platform ]]; then
	echo "error: please specify platform: native or web"
	exit 1
fi

case $platform in
	"native")
		cmake -S . -B build/$platform -DPLATFORM=$platform
		cmake --build build/$platform
		;;

	"web")
		source libs/emsdk/emsdk_env.sh
		emcmake cmake -S . -B build/$platform -DPLATFORM=$platform
		emmake make -C build/$platform #VERBOSE=1
		;;

	*)
		echo "error: unsupported platform: $platform"
		exit 1
		;;
esac


