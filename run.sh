#!/bin/bash -e

source common.sh

what=$1
if [[ ! $what ]]; then
	echo "error: please specify what to run"
	exit 1
fi

target=$(basename ${what%.*})

case $PLATFORM in
	"native")
		cmake --build build/$PLATFORM --target $target
		executable="build/$PLATFORM/${what%.*}"
		if [[ ! -f $executable ]]; then
			echo "error: file not found: ${executable}"
			exit 1
		fi	
		./${executable}
		;;

	"web")
		emmake make -C build/$PLATFORM $target --no-print-directory
		executable="build/$PLATFORM/${what%.*}.html"
		if [[ ! -f $executable ]]; then
			echo "error: file not found: ${executable}"
			exit 1
		fi	
		emrun --browser=chrome \
			--browser_info --hostname=localhost --kill_exit \
			--browser_args="--headless --remote-debugging-port=0 --disable-gpu --disable-software-rasterizer" \
			${executable}
		;;

	*)
		echo "error: unsupported platform: $PLATFORM"
		exit 1
		;;
esac