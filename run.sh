#!/usr/bin/env bash

what=$1

if [[ ! $what ]]; then
	echo "error: please specify what to run"
	exit 1
fi

executable="build/${what%.*}.html"
if [[ ! -f $executable ]]; then
	echo "error: file not found: ${executable}"
	exit 1
fi

source libs/emsdk/emsdk_env.sh
emrun --browser=chrome \
	--browser_info --hostname=localhost --kill_exit \
	--browser_args="--headless --remote-debugging-port=0 --disable-gpu --disable-software-rasterizer" \
	${executable}