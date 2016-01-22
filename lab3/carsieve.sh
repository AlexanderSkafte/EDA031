#!/bin/bash

clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ sieve.cpp -o sieve
./sieve 100
rm -f sieve

