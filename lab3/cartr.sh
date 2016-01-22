#!/bin/bash

clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ tr.cpp testtr.cpp -o tr
./tr < test.html
rm -f tr

