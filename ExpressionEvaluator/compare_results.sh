#!/bin/bash

# Extract C++ results
cpp_results=$(grep -oP '计算结果: \K[-+]?([0-9]*\.[0-9]+|[0-9]+)' cpp_output.txt)

# Extract Python results
python_results=$(grep -oP 'Result: \K[-+]?([0-9]*\.[0-9]+|[0-9]+)' python_output.txt)

# Compare each result line by line
cpp_array=($cpp_results)
python_array=($python_results)

echo "Comparing results (C++ - Python):"
num_tests=${#cpp_array[@]}
for ((i=0; i<$num_tests; i++)); do
    cpp_val=${cpp_array[i]}
    python_val=${python_array[i]}

    # Calculate the difference
    difference=$(echo "$cpp_val - $python_val" | bc -l)

    # Print comparison result
    echo "Test $((i+1)): C++ result = $cpp_val, Python result = $python_val, Difference = $difference"
done
