#!/usr/bin/env bash

what=$1
platform=$2

if [[ ! $what ]]; then
	echo "error: please specify what to run"
	exit 1
fi

if [[ ! $platform ]]; then
	echo "error: please specify platform: native or web"
	exit 1
fi

case $platform in
	"native")
		executable="build/$platform/${what%.*}"
		if [[ ! -f $executable ]]; then
			echo "error: file not found: ${executable}"
			exit 1
		fi	
		./${executable}
		;;

	"web")
		executable="build/$platform/${what%.*}.html"
		if [[ ! -f $executable ]]; then
			echo "error: file not found: ${executable}"
			exit 1
		fi	
		source libs/emsdk/emsdk_env.sh 2> /dev/null
		emrun --browser=chrome \
			--browser_info --hostname=localhost --kill_exit \
			--browser_args="--headless --remote-debugging-port=0 --disable-gpu --disable-software-rasterizer" \
			${executable}
		;;

	*)
		echo "error: unsupported platform: $platform"
		exit 1
		;;
esac