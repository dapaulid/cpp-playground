#!/bin/bash -e

if [[ ! $PLATFORM ]]; then
	export PLATFORM="native"
fi

if [ $PLATFORM = "web" ]; then
	source libs/emsdk/emsdk_env.sh 2> /dev/null
fi
