#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "word.h"
#include "dictionary.h"

using namespace std;

//
// Load a file of the format
//		...
//		hand 2 and han
//		hello 3 ell hel llo
//		...
//
Dictionary::Dictionary()
{
	ifstream		input("words.txt");
	int				size;
	string			line, word, trigram;

	// Count lines in input file, then reverse the stream
	unsigned long nlines = count(	istreambuf_iterator<char>(input),
									istreambuf_iterator<char>(), '\n') + 1;
	input.clear();
	input.seekg(0, std::ios::beg);

	cout << "Lines in file: " << nlines << endl;

	// Reserve memory for every vector in words to improve push_back speed
	for (vector<Word> v : words) {
		v.reserve(150000);
	}

	string s[250000];
	unsigned int i = 0;
	while (getline(input, line)) {
		s[i++] = line;
	}
	input.close();

	cout << "done 1" << endl;

	for (i = 0; i < 250000; ++i) {
		vector<string>	trigrams;		// XXX <---------------------
		istringstream iss(s[i]);

		// Read the first word
		iss >> word;	

		// Words must be below a certain length to be considered
		if (word.length() > max_length) {
			continue;
		}

		// Get the number of trigrams (this value is ignored)
		iss >> size;	

		// Read in all trigrams and add the to the trigrams vector
		while (iss >> trigram) {
			trigrams.push_back(trigram);
		}

		// Add Word to the vector containing words of the correct length
		words[word.length()].push_back(Word(word, trigrams));

		cout << i << endl;

		iss.clear();
	}

	cout << "done 2" << endl;

#if 0
	while (getline(input, line)) {

		istringstream iss(line);

		// Read the first word
		iss >> word;	

		// Words must be below a certain length to be considered
		if (word.length() > max_length) {
			continue;
		}

		// Get the number of trigrams (this value is ignored)
		iss >> size;	

		// Read in all trigrams and add the to the trigrams vector
		while (iss >> trigram) {
			trigrams.push_back(trigram);
		}

		// Add Word to the vector containing words of the correct length
		words[word.length()].push_back(Word(word, trigrams));

//		cout << "Parsed " << ++i << " lines." << endl;
	}

	input.close();
#endif
}

bool
Dictionary::contains(const string& word) const
{
	for (unsigned long i = 1; i < max_length + 1; ++i) {
		for (Word w : words[i]) {
			if (w.get_word() == word) {
				return true;
			}
		}
	}
	return false;
}

vector<string>
Dictionary::get_suggestions(const string& word) const
{
	vector<string> suggestions;
	add_trigram_suggestions(suggestions, word);
	rank_suggestions(suggestions, word);
	trim_suggestions(suggestions);
	return suggestions;
}

void
Dictionary::add_trigram_suggestions(vector<string>& suggestions,
									const string& word) const
{
	unsigned long wlen = word.length();
	int starting = (wlen == 1)          ? (wlen) : (wlen - 1);
	int ending   = (wlen == max_length) ? (wlen) : (wlen + 1);

	vector<Word> tmp;
	for (int i = starting; i < ending; ++i) {
		for (Word w : words[wlen]) {
			tmp.push_back(Word(w.get_word(), w.unique_trigrams()));
		}
	}
	vector<string> trigrams_misspelled = Word::unique_trigrams(word);

	for (Word w : tmp) {
		bool h = contains_at_least_half(w, trigrams_misspelled);
		if (h) {
			suggestions.push_back(w.get_word());
		}
	}
}

void
Dictionary::rank_suggestions(vector<string>& suggestions, const string& word) const
{
	vector<pair<int, string>> pairs;
	for (string& w : suggestions) {
		unsigned int dist = edit_distance(w, word);
		pairs.push_back(make_pair(dist, word));
	}
	sort(pairs.begin(), pairs.end());
	for (pair<int, string> p : pairs) {
		suggestions.push_back(p.second);
	}
}

void
Dictionary::trim_suggestions(vector<string>& suggestions) const
{
	suggestions.resize(trim_size);
}

#define CONTAINS(V, X) (find(V.begin(), V.end(), X) != V.end())
 
// true if the word contains at least half of the trigrams
bool
Dictionary::contains_at_least_half(
							const Word& word,
							const vector<string>& trigrams) const
{
	unsigned long n = 0;
	for (string& trigram : word.get_trigrams()) {
		if (CONTAINS(trigrams, trigram)) {
			n += 1;
		}
	}
	return n >= (trigrams.size() / 2);
}

unsigned int
Dictionary::edit_distance(const std::string& s1, const std::string& s2) const
{
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<vector<unsigned int>> d(len1 + 1, vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for (unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for (unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for (unsigned int i = 1; i <= len1; ++i)
		for (unsigned int j = 1; j <= len2; ++j)
			// note that std::min({arg1, arg2, arg3}) works only in C++11,
			// for C++98 use std::min(std::min(arg1, arg2), arg3)
			d[i][j] = min({
				d[i - 1][j] + 1,
				d[i][j - 1] + 1,
				d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
	return d[len1][len2];
}

