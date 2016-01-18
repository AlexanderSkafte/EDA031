#ifndef CODING_H
#define CODING_H

class Coding {
public:
	static unsigned char encode(unsigned char c);
	static unsigned char decode(unsigned char c);
private:
	static const unsigned char key = 251; // Largest prime number below 2^8 - 1
};

#endif

