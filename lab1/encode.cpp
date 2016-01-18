
#include <string>
#include <fstream>
#include <iostream>

#include "coding.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "usage: encode <file>" << std::endl;
		exit(1);
	}

	std::string filename(argv[1]);

	std::ifstream input(filename);
	if (!input) {
		std::cout << "Could not open \"" << filename << "\"." << std::endl;
		exit(1);
	}

	std::ofstream output(filename + ".enc");
	if (!output) {
		std::cout << "Could not open \"" << filename << ".enc\"." << std::endl;
		exit(1);
	}

	char c;
	while (input.get(c)) {
		output.put(Coding::encode(c));
	}

	output.close();
	input.close();
}

