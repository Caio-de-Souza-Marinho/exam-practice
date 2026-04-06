#!/bin/bash

BSQ="./bsq"
TESTS="./tests"
PASS=0
FAIL=0

run_test()
{
    local file="$1"
    local expect_error="$2"
    local name=$(basename "$file")

    stderr_out=$("$BSQ" "$file" 2>&1 1>/dev/null)
    stdout_out=$("$BSQ" "$file" 2>/dev/null)

    if [ "$expect_error" = "1" ]; then
        if echo "$stderr_out" | grep -q "map error"; then
            echo "  [PASS] $name -> map error (expected)"
            PASS=$((PASS + 1))
        else
            echo "  [FAIL] $name -> expected map error, got: '$stderr_out'"
            FAIL=$((FAIL + 1))
        fi
    else
        if echo "$stderr_out" | grep -q "map error"; then
            echo "  [FAIL] $name -> unexpected map error"
            FAIL=$((FAIL + 1))
        else
            echo "  [PASS] $name"
            echo "$stdout_out" | head -3 | sed 's/^/         /'
            PASS=$((PASS + 1))
        fi
    fi
}

echo "==============================="
echo "  BSQ TEST RUNNER"
echo "==============================="

echo ""
echo "--- VALID MAPS ---"
run_test "$TESTS/01_basic_example"         0
run_test "$TESTS/02_single_cell_empty"     0
run_test "$TESTS/03_single_cell_obstacle"  0
run_test "$TESTS/04_single_line_no_obstacles" 0
run_test "$TESTS/05_single_line_all_obstacles" 0
run_test "$TESTS/06_single_line_mixed"     0
run_test "$TESTS/07_all_empty_square"      0
run_test "$TESTS/08_all_obstacles"         0
run_test "$TESTS/09_tiebreaker_top"        0
run_test "$TESTS/10_tiebreaker_left"       0
run_test "$TESTS/11_numeric_chars"         0
run_test "$TESTS/12_symbol_chars"          0
run_test "$TESTS/13_obstacles_on_borders"  0
run_test "$TESTS/14_single_column"         0
run_test "$TESTS/15_wide_single_row"       0
run_test "$TESTS/16_tall_single_col"       0

echo ""
echo "--- INVALID MAPS (expect map error) ---"
run_test "$TESTS/17_invalid_empty_file"            1
run_test "$TESTS/18_invalid_header_only"           1
run_test "$TESTS/19_invalid_too_few_lines"         1
run_test "$TESTS/20_invalid_unequal_lengths"       1
run_test "$TESTS/21_invalid_char_in_map"           1
run_test "$TESTS/22_invalid_duplicate_empty_obstacle" 1
run_test "$TESTS/23_invalid_duplicate_empty_full"  1
run_test "$TESTS/24_invalid_duplicate_obstacle_full" 1
run_test "$TESTS/25_invalid_header_missing_field"  1
run_test "$TESTS/26_invalid_zero_lines"            1
run_test "$TESTS/27_invalid_negative_lines"        1
run_test "$TESTS/28_invalid_no_trailing_newline"   1

echo ""
echo "--- MULTI FILE TEST ---"
echo "  Running: $BSQ $TESTS/01_basic_example $TESTS/07_all_empty_square $TESTS/17_invalid_empty_file"
"$BSQ" "$TESTS/01_basic_example" "$TESTS/07_all_empty_square" "$TESTS/17_invalid_empty_file" 2>&1 | cat -A | head -15 | sed 's/^/  /'

echo ""
echo "==============================="
echo "  PASSED: $PASS  FAILED: $FAIL"
echo "==============================="
