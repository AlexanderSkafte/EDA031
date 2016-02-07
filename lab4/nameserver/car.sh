#!/bin/bash

# Run this script with   $ source car.sh

alias c+='clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++'

echo
echo "-- Compiling and running nstest.cc:"
c+ nstest.cc -o ns1 && ./ns1

echo
echo "-- Compiling and running nstime.cc with nameserverdata.txt as input:"
c+ nstime.cc -o ns2 && ./ns2 nameserverdata.txt

rm -f ns1 ns2

