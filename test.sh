#!/bin/bash -e

echo -e "\e[1;36m================================================================================\e[0m"
echo -e "\e[1;36m                            U N I T   T E S T                                   \e[0m"
echo -e "\e[1;36m================================================================================\e[0m"
rm -f coverage.info
libs/lcov/bin/lcov --zerocounters --directory src --directory test
./run.sh test/unittest
