#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using namespace std;

// Load first word of every line into unordered_set of strings
Dictionary::Dictionary() {
	ifstream input("words.txt");
	string word;
	while (input >> word) {
		words.insert(word);
		input.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	input.close();
}

bool Dictionary::contains(const string& word) const {
	return find(words.begin(), words.end(), word) != words.end();
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}

