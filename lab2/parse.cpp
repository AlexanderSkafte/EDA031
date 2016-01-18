
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
bool contains(const std::vector<T> v, const T& x)
{
	return std::find(v.begin(), v.end(), x) != v.end();
}

std::vector<std::string> unique_trigrams(std::string word)
{
	std::vector<std::string> trigrams;
	if (word.length() == 1 || word.length() == 2) {
		return trigrams;
	}
	for (unsigned long i = 0; i < word.length() - 2; ++i) {
		std::string trigram(word.substr(i, 3));
		if (!contains(trigrams, trigram)) {
			trigrams.push_back(trigram);
		}
	}
	std::sort(trigrams.begin(), trigrams.end());
	return trigrams;
}

int main(int argc, char* argv[])
{
	if (argc != 1) {
		std::cout << "usage: parse" << std::endl;
		exit(1);
	}

	std::string filename("/usr/share/dict/words");

	std::ifstream input(filename);
	if (!input) {
		std::cout << "Could not open \"" << filename << "\"." << std::endl;
		exit(1);
	}

	std::ofstream output("words.txt");
	if (!output) {
		std::cout << "Could not open \"words.txt\"." << std::endl;
		exit(1);
	}

	std::string word;
	while (input >> word) {
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		std::vector<std::string> trigrams = unique_trigrams(word);
		output << word << " " << trigrams.size();
		if (trigrams.size() > 0) {
			for (auto& trigram : trigrams) {
				output << " " << trigram;
			}
		}
		output << std::endl;
	}

	output.close();
	input.close();
}

