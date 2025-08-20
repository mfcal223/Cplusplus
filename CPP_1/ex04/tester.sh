#!/bin/bash

# tester.sh for ex04 - Sed is for losers

# clean old replace files
rm -f text.replace
make re

echo "=== Test 1: Replace 'my collegue' with 'the Lizard' ==="
echo "Input file content:"
cat text
echo "-------------------"

./sedisforlosers text "my collegue" "the Lizard"

echo "Output file (text.replace) content:"
cat text.replace
echo "=================== END TEST 1 ==================="
echo ""

# Add more tests as needed
echo "=== Test 2: No matches (replace 'banana' with 'apple') ==="
rm -f text.replace
./sedisforlosers text "banana" "apple"

echo "Output file (text.replace) content:"
cat text.replace
echo "=================== END TEST 2 ==================="
echo ""

echo "=== Test 3: s1 == s2 (no changes expected) ==="
rm -f text.replace
./sedisforlosers text "my collegue" "my collegue"

echo "Output file (text.replace) content:"
cat text.replace
echo "=================== END TEST 3 ==================="

make fclean