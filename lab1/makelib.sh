clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ -c coding.cpp && \
clang++ -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -stdlib=libc++ -c list.cc && \
ar crv liblab1.a coding.o list.o
