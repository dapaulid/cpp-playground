#!/bin/bash -e

source libs/emsdk/emsdk_env.sh
emcmake cmake -S . -B build
emmake make -C build #VERBOSE=1
