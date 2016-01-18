#include "coding.hpp"

unsigned char
Coding::encode(unsigned char c) {
	return c ^ key;
}

unsigned char
Coding::decode(unsigned char c) {
	return c ^ key;
}

