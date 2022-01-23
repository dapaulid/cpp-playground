#!/usr/bin/env bash

# exit on error
set -e

# function for setting up a single submodule/library
setup_submodule() {
	modname=$1
	cmake_args=${@:2}
	echo
	echo "================================================================================"
	echo "> setting up $modname"
	echo "================================================================================"
	echo "[ git submodule ]"
	git submodule update --init --recursive libs/$modname
	git submodule status libs/$modname
	echo "[ cmake ]"
	cmake -S libs/$modname -B build/libs/$modname $cmake_args
	echo "[ make ]"
	make -C build/libs/$modname	
	echo "[ done ]"
}

# do all submodules here
setup_submodule "googletest"
setup_submodule "benchmark" "-DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_TESTING=OFF"

# done
echo
echo "================================================================================"
echo "setup completed successfully!"
