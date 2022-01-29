#!/bin/bash -e

emcmake cmake -S . -B build
emmake make -C build #VERBOSE=1
