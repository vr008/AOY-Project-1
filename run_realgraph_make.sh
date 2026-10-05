#!/bin/bash

echo "================================"
echo "Running Real-Life Graph Bonus"
echo "================================"
echo ""

echo "Compiling..."

g++ -std=c++17 graph_operations.cpp realgraph_make.cpp -o real_graph_test

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Compilation successful."
echo ""

rm -f real_results.txt
rm -f bonus_memory.txt

echo "Starting bonus experiment..."
echo ""

 /usr/bin/time -v -o bonus_memory.txt ./real_graph_test

STATUS=$?

echo ""

if [ $STATUS -ne 0 ]; then
    echo "ERROR: Program exited with code $STATUS"
    echo ""
    echo "Memory information:"
    cat bonus_memory.txt
    exit $STATUS
fi

echo "Adding CPU and memory information..."

echo "" >> real_results.txt
echo "PROCESS-LEVEL MEASUREMENTS" >> real_results.txt
echo "===========================" >> real_results.txt

grep "Maximum resident set size" bonus_memory.txt >> real_results.txt
grep "User time" bonus_memory.txt >> real_results.txt
grep "System time" bonus_memory.txt >> real_results.txt
grep "Elapsed" bonus_memory.txt >> real_results.txt

rm -f bonus_memory.txt

echo ""
echo "================================"
echo "Bonus experiment finished."
echo "Results saved to real_results.txt"
echo "================================"