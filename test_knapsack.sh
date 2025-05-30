#!/bin/bash
# filepath: /Users/sergio/code/greedy_dp/run_knapsack_tests.sh

EXE=./build/knapsack_test
for n in $(seq 100 100 1000); do
  echo "===== n = $n ====="
  for i in {1..10}; do
    $EXE $n
  done
done