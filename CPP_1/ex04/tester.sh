#!/bin/bash

# tester.sh for ex04 - Sed is for losers

# clean old replace files
rm -f text.replace
make re

echo ""
echo "====== INPUT FILE CONTENT =======:"
cat text
echo ""
echo "-----------------------------------------------------------------"
echo ""
echo "===================== TEST 1 ==================="
echo "=== Test 1: Replace 'my collegue' with 'the Lizard' ==="
./sedisforlosers text "my collegue" "the Lizard"

echo "Output file (text.replace) content:"
echo ""
cat text.replace
echo "=================== END TEST 1 ==================="
echo ""

echo "===================== TEST 2 ==================="
echo "=== Test 2: No matches (replace 'banana' with 'apple') ==="
rm -f text.replace
./sedisforlosers text "banana" "apple"

echo "Output file (text.replace) content:"
echo ""
cat text.replace
echo "=================== END TEST 2 ==================="
echo ""

echo "===================== TEST 3 ==================="
echo "=== Test 3: s1 == s2 (no changes expected) ==="
rm -f text.replace
./sedisforlosers text "my collegue" "my collegue"

echo "Output file (text.replace) content:"
echo ""
cat text.replace
echo "=================== END TEST 3 ==================="
echo ""

echo "===================== TEST 4 ==================="
echo "=== Test 4: Wrong filename ==="
./sedisforlosers notfound "my collegue" "the Lizard"
echo "=================== END TEST 4 ==================="
echo ""

echo "===================== TEST 5 ==================="
echo "=== Test 5: No arguments ==="
./sedisforlosers
echo "=================== END TEST 5 ==================="
echo ""

echo "===================== TEST 6 ==================="
echo "=== Test 6: Missing 1 argument (only filename given) ==="
./sedisforlosers text
echo "=================== END TEST 6 ==================="
echo ""

make fclean