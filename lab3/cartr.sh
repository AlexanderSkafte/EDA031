clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ tr.cpp test_tr.cpp -o tr && \
cat test.html | ./tr
