#!/bin/bash

args=("$@")

alias c+='clang++ ${args[0]} ${args[1]} -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++'

c+ parse.cpp -o parse
echo "--- Parsing '/usr/share/dict/words' and generating 'words.txt':"
./parse # generates words.txt
rm -f parse
echo "--- Done parsing."
echo

c+ word.cc dictionary.cc spell.cc -o spell
echo "--- Running spellcheck program:"
./spell 
rm -f spell
echo "--- Closed spellcheck program."
echo

