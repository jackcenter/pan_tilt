#!/bin/bash

TESTS_DIR="./build/test/tests"

# Loop through all test in the tests directory
for test in "$TESTS_DIR"/*; do
  # Check if the file is executable
  if [[ -x "$test" && -f "$test" ]]; then
    "$test" # Execute the file
  fi
done
