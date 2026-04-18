#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
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
failed_tests=()

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
        if echo "$output" | grep -q "Error"; then
            echo -ne "."
            ((passed++))
        else
            echo -ne "F"
            failed_tests+=("FAIL: $test_name (Expected Error, got: ${output:0:50})")
        fi
    elif [[ "$expected_output" == "NO_ERROR" ]]; then
        if ! echo "$output" | grep -q "Error"; then
            echo -ne "."
            ((passed++))
        else
            echo -ne "F"
            failed_tests+=("FAIL: $test_name (Unexpected Error)")
        fi
    elif [[ "$expected_output" == "NO_LEAK" ]]; then
        if echo "$output" | grep -q "All heap blocks were freed"; then
            echo -ne "."
            ((passed++))
        else
            echo -ne "F"
            failed_tests+=("FAIL: $test_name (Memory leak detected)")
        fi
    fi
}

echo "=== Aggressive Test Suite ==="
echo ""
echo "Running tests (. = pass, F = fail):"
echo ""

# ========== BASIC EDGE CASES ==========
echo -n "Edge cases: "

run_test "Only flag" "./push_swap --simple" "ERROR"
run_test "Only bench flag" "./push_swap --bench" "ERROR"
run_test "Zero" "./push_swap 0" "NO_ERROR"
run_test "Single large number" "./push_swap 2147483647" "NO_ERROR"
run_test "Single negative large" "./push_swap -2147483648" "NO_ERROR"
run_test "Zero with others" "./push_swap 0 1 2 3" "NO_ERROR"
run_test "All zeros" "./push_swap 0 0 0" "ERROR"
run_test "Two same numbers" "./push_swap 5 5" "ERROR"
run_test "Three same numbers" "./push_swap 7 7 7" "ERROR"

echo ""
echo -n "Invalid flags: "

run_test "Flag --" "./push_swap -- 1 2 3" "ERROR"
run_test "Flag ---simple" "./push_swap ---simple 1 2 3" "ERROR"
run_test "Flag --1" "./push_swap --1 1 2 3" "ERROR"
run_test "Flag --xyz" "./push_swap --xyz 1 2 3" "ERROR"
run_test "Flag --Simple (case sensitive)" "./push_swap --Simple 1 2 3" "ERROR"
run_test "Flag --SIMPLE (uppercase)" "./push_swap --SIMPLE 1 2 3" "ERROR"
run_test "Multiple dashes" "./push_swap ---- 1 2 3" "ERROR"
run_test "Flag with space --si mple" "./push_swap \"--si mple\" 1 2" "ERROR"
run_test "Empty flag" "./push_swap -- \"\" 1 2" "ERROR"

echo ""
echo -n "Duplicate flags: "

run_test "Two simple flags" "./push_swap --simple 1 2 --simple 3" "ERROR"
run_test "Two medium flags" "./push_swap --medium 1 2 --medium 3" "ERROR"
run_test "Two complex flags" "./push_swap --complex 1 2 --complex 3" "ERROR"
run_test "Two adaptive flags" "./push_swap --adaptive 1 2 --adaptive 3" "ERROR"
run_test "Three same flags" "./push_swap --simple 1 --simple 2 --simple 3" "ERROR"
run_test "Flags at start and end" "./push_swap --simple 1 2 3 --simple" "ERROR"
run_test "Flags surrounded by numbers" "./push_swap 1 --simple 2 --simple 3" "ERROR"

echo ""
echo -n "Conflicting flags: "

run_test "Simple and medium" "./push_swap --simple 1 2 --medium 3" "ERROR"
run_test "Simple and complex" "./push_swap --simple 1 2 --complex 3" "ERROR"
run_test "Medium and adaptive" "./push_swap --medium 1 2 --adaptive 3" "ERROR"
run_test "Complex and simple" "./push_swap --complex 1 2 --simple 3" "ERROR"
run_test "All four flags" "./push_swap --simple 1 --medium 2 --complex 3 --adaptive 4" "ERROR"
run_test "Three different flags" "./push_swap --simple --medium --complex 1 2 3" "ERROR"

echo ""
echo -n "Invalid numbers: "

run_test "Letters" "./push_swap 1 abc 3" "ERROR"
run_test "Float numbers" "./push_swap 1 2.5 3" "ERROR"
run_test "Hex numbers" "./push_swap 0x10 0x20" "ERROR"
run_test "Mixed alphanumeric" "./push_swap 1a2b3c" "ERROR"
run_test "Special characters" "./push_swap 1 2 @#$" "ERROR"
run_test "Empty string" "./push_swap \"\"" "ERROR"
run_test "Just spaces" "./push_swap \"   \"" "ERROR"
run_test "Tab character" "./push_swap $'1\t2\t3'" "ERROR"
run_test "Newline in args" "./push_swap $'1\n2\n3'" "ERROR"

echo ""
echo -n "Duplicate numbers (error cases): "

run_test "Two same at start" "./push_swap 5 5 1 2 3" "ERROR"
run_test "Two same at end" "./push_swap 1 2 3 5 5" "ERROR"
run_test "Two same in middle" "./push_swap 1 5 5 2 3" "ERROR"
run_test "Three of same number" "./push_swap 1 2 3 3 3 4" "ERROR"
run_test "Multiple duplicates" "./push_swap 1 1 2 2 3 3" "ERROR"
run_test "Duplicates with flag" "./push_swap --simple 5 2 5" "ERROR"
run_test "Duplicates negative" "./push_swap -5 2 -5" "ERROR"
run_test "Duplicates with zero" "./push_swap 0 1 0" "ERROR"

echo ""
echo -n "Valid cases (sorted/unsorted): "

run_test "Already sorted ascending" "./push_swap 1 2 3 4 5" "NO_ERROR"
run_test "Sorted descending" "./push_swap 5 4 3 2 1" "NO_ERROR"
run_test "Reverse pairs" "./push_swap 2 1 4 3" "NO_ERROR"
run_test "Random order 5 nums" "./push_swap 3 1 4 2 5" "NO_ERROR"
run_test "Negative numbers" "./push_swap -5 -2 -10 -1" "NO_ERROR"
run_test "Mixed negative positive" "./push_swap -5 0 5 -1 1" "NO_ERROR"
run_test "Large range numbers" "./push_swap -1000000 1000000 0 500000" "NO_ERROR"
run_test "Single number" "./push_swap 42" "NO_ERROR"
run_test "Two numbers" "./push_swap 2 1" "NO_ERROR"

echo ""
echo -n "Flags with valid args: "

run_test "Simple flag 5 nums" "./push_swap --simple 3 1 4 2 5" "NO_ERROR"
run_test "Medium flag 5 nums" "./push_swap --medium 3 1 4 2 5" "NO_ERROR"
run_test "Complex flag 5 nums" "./push_swap --complex 3 1 4 2 5" "NO_ERROR"
run_test "Adaptive flag 5 nums" "./push_swap --adaptive 3 1 4 2 5" "NO_ERROR"
run_test "Bench flag" "./push_swap --bench 5 2 3 1" "NO_ERROR"
run_test "Bench with simple" "./push_swap --simple --bench 5 2 3 1" "NO_ERROR"
run_test "Bench at end" "./push_swap 5 2 3 1 --bench" "NO_ERROR"
run_test "Bench in middle" "./push_swap 5 2 --bench 3 1" "NO_ERROR"

echo ""
echo -n "Quoted arguments: "

run_test "Quote single arg" "./push_swap \"5\"" "NO_ERROR"
run_test "Quote multiple" "./push_swap \"5 2 4 1\"" "NO_ERROR"
run_test "Quote with flag" "./push_swap \"--simple 5 2 4\"" "NO_ERROR"
run_test "Mixed quotes and args" "./push_swap 5 \"2 4\" 1" "NO_ERROR"
run_test "Quote empty string" "./push_swap \"\"" "ERROR"
run_test "Quote only spaces" "./push_swap \"   \"" "ERROR"
run_test "Multiple quoted args" "./push_swap \"1 2\" \"3 4\" \"5\"" "NO_ERROR"

echo ""
echo -n "Flag positions: "

run_test "Flag at start" "./push_swap --simple 5 2 4 1" "NO_ERROR"
run_test "Flag at end" "./push_swap 5 2 4 1 --simple" "NO_ERROR"
run_test "Flag in middle" "./push_swap 5 2 --simple 4 1" "NO_ERROR"
run_test "Flag after second arg" "./push_swap 5 --simple 2 4 1" "NO_ERROR"
run_test "Flag before last arg" "./push_swap 5 2 4 --simple 1" "NO_ERROR"

echo ""
echo -n "Large inputs: "

run_test "10 numbers" "./push_swap 1 5 3 9 2 8 4 7 6 10" "NO_ERROR"
run_test "20 numbers" "./push_swap $(seq 1 20 | shuf)" "NO_ERROR"
run_test "50 numbers" "./push_swap $(seq 1 50 | shuf)" "NO_ERROR"
run_test "100 numbers" "./push_swap $(seq 1 100 | shuf)" "NO_ERROR"

echo ""
echo -n "Memory leak tests: "

run_test "Leak - invalid flag" "valgrind --leak-check=full ./push_swap --invalid 5 2 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - duplicate flags" "valgrind --leak-check=full ./push_swap --simple 1 2 --simple 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - normal simple" "valgrind --leak-check=full ./push_swap --simple 5 2 4 1 3 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - normal medium" "valgrind --leak-check=full ./push_swap --medium 5 2 4 1 3 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - normal complex" "valgrind --leak-check=full ./push_swap --complex 5 2 4 1 3 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - duplicate numbers" "valgrind --leak-check=full ./push_swap 5 2 4 2 1 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - conflicting flags" "valgrind --leak-check=full ./push_swap --simple 1 --medium 2 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - quoted args" "valgrind --leak-check=full ./push_swap \"5 2 4 1\" 2>&1 | grep 'All heap'" "NO_LEAK"
run_test "Leak - large input" "valgrind --leak-check=full ./push_swap $(seq 1 50 | shuf) 2>&1 | grep 'All heap'" "NO_LEAK"

echo ""
echo ""
echo "=== Test Results ==="
printf "Total: %d\n" $total
printf "Passed: ${GREEN}%d${NC}\n" $passed
printf "Failed: ${RED}%d${NC}\n" $((total - passed))
echo ""

if [ ${#failed_tests[@]} -gt 0 ]; then
    echo "=== Failed Tests ==="
    for test in "${failed_tests[@]}"; do
        echo -e "${RED}$test${NC}"
    done
    echo ""
fi

if [ $passed -eq $total ]; then
    echo -e "${GREEN}✓ All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Some tests failed.${NC}"
    exit 1
fi
