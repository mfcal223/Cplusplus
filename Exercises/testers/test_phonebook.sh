#!/bin/bash

# Compile program
make re

# Run program and feed test inputs
./phonebook <<EOF
ADD
John
Doe
JD
1234567890
Loves pizza
ADD
Jane
Smith
JS
0987654321
Hates pineapple
ADD
Alice
Brown
Ally
1112223333
Secret agent
ADD
Bob
White
Bobby
4445556666
Afraid of heights
ADD
Charlie
Black
Chuck
7778889999
Collects stamps
ADD
Diana
Green
Di
0001112222
Can juggle
ADD
Edward
Blue
Ed
3334445555
Never sleeps
ADD
Fiona
Yellow
Fi
6667778888
Knows 5 languages
SEARCH
4
ADD
Shrek
Green
Shr3k
9967778558
Studies at 42
SEARCH
0
SEARCH
1
ADD
Michaelangelo
Mouse
Mickey
123456789
Uses pink underwear
SEARCH
1
EXIT
EOF
