#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "word.h"
#include "dictionary.h"

#define DEBUG(X)
//#define DEBUG(X) do { X; } while (0);

using namespace std;

// Load a file of the format
//		...
//		hand 2 and han
//		hello 3 ell hel llo
//		...
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

	cout << "Lines in file 'words.txt': " << nlines << endl;

	// Reserve memory for every vector in words to improve push_back speed
	for (vector<Word> v : words) {
		v.reserve(15000);
	}

	while (getline(input, line)) {

		vector<string>	trigrams;
		istringstream	iss(line);

		// Read the first word
		iss >> word;	

		// Words must be below a certain length to be considered
		if (word.length() > MAX_LENGTH) {
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

		// This may be completely unnecessary
		iss.clear();
	}
	input.close();

	// Shrink every vector to save space
	for (vector<Word> v : words) {
		v.shrink_to_fit();
	}

	cout << "Created dictionary." << endl;
}

bool
Dictionary::contains(const string& word) const
{
	for (unsigned long i = 1; i <= MAX_LENGTH; ++i) {
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
	DEBUG(
		cout << "Suggestions after add:" << endl;
		for (const string& s : suggestions)
			cout << "  " << s << endl;
	);
	rank_suggestions(suggestions, word);
	DEBUG(
		cout << "Suggestions after add:" << endl;
		for (const string& s : suggestions)
			cout << "  " << s << endl;
	);
	trim_suggestions(suggestions);
	DEBUG(
		cout << "Suggestions after add:" << endl;
		for (const string& s : suggestions)
			cout << "  " << s << endl;
	);
	return suggestions;
}

void
Dictionary::add_trigram_suggestions(vector<string>& suggestions,
									const string& word) const
{
	unsigned long wlen = word.length();
	if (wlen < 1) { return; }
	int starting = (wlen == 1)          ? (wlen) : (wlen - 1);
	int ending   = (wlen == MAX_LENGTH) ? (wlen) : (wlen + 1);
	vector<Word> tmp;
	for (int i = starting; i <= ending; ++i) {
		for (Word w : words[i]) {
			tmp.push_back(Word(w.get_word(), Word::unique_trigrams(w)));
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
	for (const string& w : suggestions) {
		unsigned int dist = edit_distance(w, word);
		pairs.push_back(make_pair(dist, w));
	}
	using P = pair<int, string>;
	auto compare = [](P p1, P p2){ return p1.first < p2.first; };
	sort(pairs.begin(), pairs.end(), compare);
	suggestions.clear();
	for (pair<int, string> p : pairs) {
		DEBUG(
			cout << "Pushing (" <<  p.first << ") " << p.second << endl;
		);
		suggestions.push_back(p.second);
	}
}

void
Dictionary::trim_suggestions(vector<string>& suggestions) const
{
	suggestions.resize(TRIM_SIZE);
}

#define CONTAINS(V, X) (find(V.begin(), V.end(), X) != V.end())

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
	for (unsigned int i = 1; i <= len1; ++i) { d[i][0] = i; }
	for (unsigned int i = 1; i <= len2; ++i) { d[0][i] = i; }
	for (unsigned int i = 1; i <= len1; ++i) {
		for (unsigned int j = 1; j <= len2; ++j) {
			// note that std::min({arg1, arg2, arg3}) works only in C++11,
			// for C++98 use std::min(std::min(arg1, arg2), arg3)
			d[i][j] = min({
				d[i - 1][j] + 1,
				d[i][j - 1] + 1,
				d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
		}
	}
	DEBUG(
		cout << "Edit distance for \"" << s1 << "\": " << d[len1][len2] << endl;
	);
	return d[len1][len2];
}

