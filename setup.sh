#!/bin/bash -e

# color constants
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# function for setting up a single submodule/library
setup_submodule() {
	modname=$1
	cmake_args=${@:2}
	echo
	echo "================================================================================"
	echo -e "> setting up ${YELLOW}$modname${NC}"
	echo "================================================================================"
	echo -e "[ ${WHITE}git submodule${NC} ]"
	git submodule update --init --recursive libs/$modname
	git submodule status libs/$modname
	echo -e "[ ${WHITE}configure${NC} ]"
	cmake -S libs/$modname -B build/libs/$modname $cmake_args
	echo -e "[ ${WHITE}build${NC} ]"
	cmake --build build/libs/$modname	
	echo -e "[ ${GREEN}done${NC} ]"
}

# output some version info
git --version
cmake --version

# do all submodules here
setup_submodule "googletest"
setup_submodule "benchmark" "-DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_TESTING=OFF"

# done
echo
echo "================================================================================"
echo "setup completed successfully!"
