#!/usr/bin/env bash

# exit on error
set -e

echo
echo "================================================================================"
echo "> building googletest"
echo "================================================================================"
cmake -S libs/googletest -B build/libs/googletest
make -C build/libs/googletest

echo
echo "================================================================================"
echo "> building google benchmark"
echo "================================================================================"
cmake -S libs/benchmark -B build/libs/benchmark -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF #-DGOOGLETEST_PATH=libs/googletest
make -C build/libs/benchmark

echo
echo "================================================================================"
echo "setup completed successfully!"
