#!/bin/bash

clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ encode.cpp coding.cpp -o encode
clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ decode.cpp coding.cpp -o decode

echo
echo "-- Before encoding:"
cat ode.txt

./encode ode.txt

echo
echo "-- After encoding:"
cat ode.txt.enc

./decode ode.txt.enc

echo
echo "-- After decoding:"
cat ode.txt.enc.dec

echo

rm -f encode decode ode.txt.enc ode.txt.enc.dec

