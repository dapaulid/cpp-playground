#!/bin/bash -e

# color constants
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

EMSDK_VERSION='3.1.2' # check with ./emsdk list

prepare_submodule() {
	modname=$1
	echo
	echo "================================================================================"
	echo -e "> setting up ${YELLOW}$modname${NC}"
	echo "================================================================================"
	echo -e "[ ${WHITE}git submodule${NC} ]"
	git submodule update --init --recursive libs/$modname
	git submodule status libs/$modname	
}

# function for setting up a single submodule/library
cmake_submodule() {
	modname=$1
	cmake_args=${@:2}
	prepare_submodule $modname
	echo -e "[ ${WHITE}configure${NC} ]"
	cmake -S libs/$modname -B build/libs/$modname $cmake_args
	echo -e "[ ${WHITE}build${NC} ]"
	cmake --build build/libs/$modname	
	echo -e "[ ${GREEN}done${NC} ]"
}

# output some version info
git --version
cmake --version

# setup googletest
cmake_submodule "googletest"

# setup google benchmark
cmake_submodule "benchmark" "-DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_TESTING=OFF"

# setup lcov
prepare_submodule "lcov"
echo -e "[ ${WHITE}check${NC} ]"
libs/lcov/bin/lcov -v
echo -e "[ ${GREEN}done${NC} ]"

# setup emscripten
prepare_submodule "emsdk"
echo -e "[ ${WHITE}install${NC} ]"
libs/emsdk/emsdk install $EMSDK_VERSION
libs/emsdk/emsdk activate $EMSDK_VERSION
source libs/emsdk/emsdk_env.sh
echo -e "[ ${WHITE}check${NC} ]"
libs/emsdk/upstream/emscripten/em++ --check
echo -e "[ ${GREEN}done${NC} ]"

# done
echo
echo "================================================================================"
echo "setup completed successfully!"
