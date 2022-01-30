#!/usr/bin/env bash

source libs/emsdk/emsdk_env.sh
emrun --browser=chrome \
	--browser_info --hostname=localhost --kill_exit \
	--browser_args="--headless --remote-debugging-port=0 --disable-gpu --disable-software-rasterizer" \
	build/example.html