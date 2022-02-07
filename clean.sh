#!/bin/bash -e

platform=$1

if [[ ! $platform ]]; then
	echo "error: please specify platform: native or web"
	exit 1
fi

#cmake --build build/$platform --target clean
rm -rf build/$platform