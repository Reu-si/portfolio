#!/bin/bash

PROGRAM=./replace
PASS_COUNT=0
FAIL_COUNT=0

# Utility: Run a test case
run_test() {
    desc="$1"
    input="$2"
    s1="$3"
    s2="$4"
    expected="$5"

    echo -n "Test: $desc ... "

    # Setup input file
    echo -e "$input" > test.txt

    # Run replace
    $PROGRAM test.txt "$s1" "$s2" > /dev/null 2>&1

    # Check if output file exists
    if [ ! -f test.txt.replace ]; then
        echo "❌ (no output file)"
        ((FAIL_COUNT++))
        return
    fi

    # Read output
    actual=$(cat test.txt.replace)

    if [ "$actual" == "$expected" ]; then
        echo "✅"
        ((PASS_COUNT++))
    else
        echo "❌"
        echo "Expected:"
        echo "$expected"
        echo "Actual:"
        echo "$actual"
        ((FAIL_COUNT++))
    fi

    rm -f test.txt test.txt.replace
}

# Test 1: Basic replace
run_test "Basic replace" \
"Hello world
world is big" \
"world" "universe" \
"Hello universe
universe is big"

# Test 2: s1 not found
run_test "s1 not found" \
"No matching word here" \
"banana" "apple" \
"No matching word here"

# Test 3: Multiple matches in line
run_test "Multiple matches in one line" \
"foo foo foo" \
"foo" "bar" \
"bar bar bar"

# Test 4: Empty file
run_test "Empty file" \
"" \
"a" "b" \
""

# Test 5: s1 is empty (should not run)
echo -n "Test: s1 is empty ... "
$PROGRAM test.txt "" "x" > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "✅"
    ((PASS_COUNT++))
else
    echo "❌"
    ((FAIL_COUNT++))
fi
rm -f test.txt test.txt.replace

# Test 6: s1 == s2 (no visible change)
run_test "s1 equals s2" \
"copy this copy please" \
"copy" "copy" \
"copy this copy please"

# Test 7: Input file does not exist
echo -n "Test: file does not exist ... "
$PROGRAM nofile.txt test test > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "✅"
    ((PASS_COUNT++))
else
    echo "❌"
    ((FAIL_COUNT++))
fi

# Summary
echo
echo "Passed: $PASS_COUNT"
echo "Failed: $FAIL_COUNT"

if [ $FAIL_COUNT -eq 0 ]; then
    echo "🎉 All tests passed!"
else
    echo "❗ Some tests failed."
fi