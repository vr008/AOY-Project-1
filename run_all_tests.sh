#!/bin/bash

echo "Compiling..."

g++ -std=c++17 graph_operations.cpp graph_simulator.cpp simulated_test.cpp -o graph_test

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Compilation successful."
echo ""

# Start a fresh results file
rm -f results.txt

echo "Graph Algorithms Experiment Results" >> results.txt
echo "===================================" >> results.txt
echo "" >> results.txt


run_test()
{
    TYPE=$1
    SIZE=$2

    echo "Running $TYPE $SIZE..."

    /usr/bin/time -v \
        -o memory.txt \
        ./graph_test "$TYPE" "$SIZE"

    echo "Peak memory:" >> results.txt

    grep "Maximum resident set size" memory.txt >> results.txt

    echo "User time:" >> results.txt

    grep "User time" memory.txt >> results.txt

    echo "System time:" >> results.txt

    grep "System time" memory.txt >> results.txt

    echo "Elapsed time:" >> results.txt

    grep "Elapsed" memory.txt >> results.txt

    echo "" >> results.txt
}


# Cycle
run_test cycle 1000
run_test cycle 5000
run_test cycle 10000

# Complete
run_test complete 100
run_test complete 500
run_test complete 1000

# Empty
run_test empty 1000
run_test empty 5000
run_test empty 10000

# Heap
run_test heap 1000
run_test heap 5000
run_test heap 10000


rm -f memory.txt

echo ""
echo "================================"
echo "All experiments finished."
echo "Results saved to results.txt"
echo "================================"