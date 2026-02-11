#!/bin/bash -e

# Compile
echo "Compiling..."
g++ -g -std=c++17 astar_dojo.cpp -o dojo

# Run
if [ $? -eq 0 ]; then
    echo "=================================="
    # Uses $1 if provided, otherwise defaults to basic_tests.txt
    TEST_FILE=${1:-basic_tests.txt}
    ./dojo "$TEST_FILE"
    rm dojo
else
    echo "❌ Compilation Error."
fi
