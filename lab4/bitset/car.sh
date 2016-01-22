#!/bin/bash

# Run this script with   $ source car.sh

alias c+='clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++'

c+ simplebitset.cc simplebitsettest.cc      -o sb && ./sb > outsb
c+ bitreference.cc bitset.cc bitsettest1.cc -o b1 && ./b1 > outb1
c+ bitreference.cc bitset.cc bitsettest2.cc -o b2 && ./b2 > outb2

echo
echo "-- Correct output:"
cat correct

echo
echo "-- Output from simple bit test:"
cat outsb

echo
echo "-- Output from bit test 1:"
cat outb1

echo
echo "-- Output from bit test 2:"
cat outb2

echo
echo "-- Diff simple bit test:"
diff outsb correct

echo
echo "-- Diff bit test 1:"
diff outb1 correct

echo
echo "-- Diff bit test 2:"
diff outb2 correct

echo
rm -f sb b1 b2 outsb outb1 outb2

