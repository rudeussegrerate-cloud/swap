#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Compile the project first
echo "Compiling project..."
make clean > /dev/null 2>&1
make > /dev/null 2>&1
if [ ! -f ./push_swap ]; then
    echo "Error: Failed to compile push_swap"
    exit 1
fi
echo "Compilation successful!"
echo ""

# Test counter
total=0
passed=0

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_output="$3"
    
    ((total++))
    
    # Run command and capture output
    output=$(eval "$command" 2>&1)
    exit_code=$?
    
    # Check if test passed
    if [[ "$expected_output" == "ERROR" ]]; then
        # Test expects an Error output
        if echo "$output" | grep -q "Error"; then
            echo "PASS: $test_name"
            ((passed++))
        else
            echo "FAIL: $test_name (Expected Error, got: $output)"
        fi
    elif [[ "$expected_output" == "NO_ERROR" ]]; then
        # Test expects successful run (no Error output)
        if ! echo "$output" | grep -q "Error"; then
            echo "PASS: $test_name"
            ((passed++))
        else
            echo "FAIL: $test_name (Unexpected Error)"
        fi
    elif [[ "$expected_output" == "NO_LEAK" ]]; then
        # Test with valgrind - check for no memory leaks
        if echo "$output" | grep -q "All heap blocks were freed"; then
            echo "PASS: $test_name"
            ((passed++))
        else
            echo "FAIL: $test_name (Memory leak detected)"
        fi
    fi
}

echo "=== Push Swap Test Suite ==="
echo ""

# Test 1: Invalid flag
run_test "Invalid flag --invalid" "./push_swap --invalid 5 2" "ERROR"

# Test 2: Invalid flag --2
run_test "Invalid flag --2" "./push_swap --2 5 2" "ERROR"

# Test 3: Duplicate flags
run_test "Duplicate flags" "./push_swap --simple 1 2 3 --simple" "ERROR"

# Test 4: Conflicting flags
run_test "Conflicting flags" "./push_swap --simple 1 2 --medium 3" "ERROR"

# Test 5: Duplicate numbers
run_test "Duplicate numbers" "./push_swap 5 2 4 2 1" "ERROR"

# Test 6: Normal case with --simple flag
run_test "Normal case --simple" "./push_swap --simple 5 2 4 1 3" "NO_ERROR"

# Test 7: Normal case with --medium flag
run_test "Normal case --medium" "./push_swap --medium 5 2 4 1 3" "NO_ERROR"

# Test 8: Normal case with --complex flag
run_test "Normal case --complex" "./push_swap --complex 5 2 4 1 3" "NO_ERROR"

# Test 9: Normal case with --adaptive flag
run_test "Normal case --adaptive" "./push_swap --adaptive 5 2 4 1 3" "NO_ERROR"

# Test 10: Normal case without flag
run_test "Normal case no flag" "./push_swap 5 2 4 1 3" "NO_ERROR"

# Test 11: Quoted arguments
run_test "Quoted arguments" "./push_swap --complex 5 2 \"4 1 3\"" "NO_ERROR"

# Test 12: Bench flag
run_test "Bench flag" "./push_swap --bench 5 2 4 1 3" "NO_ERROR"

# Test 13: Single number
run_test "Single number" "./push_swap 5" "NO_ERROR"

# Test 14: Two numbers
run_test "Two numbers" "./push_swap 5 2" "NO_ERROR"

# Test 15: Negative numbers
run_test "Negative numbers" "./push_swap -5 2 -4 1 3" "NO_ERROR"

# Test 16: Large numbers
run_test "Large numbers" "./push_swap 2147483647 -2147483648 0 100" "NO_ERROR"

# Test 17: Empty arguments
run_test "Empty arguments" "./push_swap \"\"" "ERROR"

# Test 18: Non-numeric values
run_test "Non-numeric values" "./push_swap 5 abc 3" "ERROR"

# Test 19: Flag in the middle
run_test "Flag in the middle" "./push_swap 5 2 --simple 4 1 3" "NO_ERROR"

# Test 20: Multiple arguments in quotes
run_test "Multiple arguments in quotes" "./push_swap \"5 2 4 1 3\"" "NO_ERROR"

echo ""
echo "=== Memory Leak Tests (Valgrind) ==="
echo ""

# Memory leak tests
run_test "No leak - invalid flag" "valgrind --leak-check=full ./push_swap --invalid 5 2 2>&1 | grep -E 'All heap|definitely lost'" "NO_LEAK"

run_test "No leak - duplicate flags" "valgrind --leak-check=full ./push_swap --simple 1 2 3 --simple 2>&1 | grep -E 'All heap|definitely lost'" "NO_LEAK"

run_test "No leak - normal case" "valgrind --leak-check=full ./push_swap --simple 5 2 4 1 3 2>&1 | grep -E 'All heap|definitely lost'" "NO_LEAK"

run_test "No leak - duplicate numbers" "valgrind --leak-check=full ./push_swap 5 2 4 2 1 2>&1 | grep -E 'All heap|definitely lost'" "NO_LEAK"

run_test "No leak - quoted args" "valgrind --leak-check=full ./push_swap --complex 5 2 \"4 1 3\" 2>&1 | grep -E 'All heap|definitely lost'" "NO_LEAK"

echo ""
echo "=== Test Results ==="
echo "Total: $total"
echo "Passed: $passed"
echo "Failed: $((total - passed))"

if [ $passed -eq $total ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi
