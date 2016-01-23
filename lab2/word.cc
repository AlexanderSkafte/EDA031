#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t)
	: word_{w}
	, trigrams_{t}
{ /* intentionally empty */ }

// TODO - Make more effictient.
//			"You may assume that the trigrams in the parameter vector also are
//			sorted in alphabetical order. Use this fact to write an efficient
//			implementation of get matches."
#define CONTAINS(V, X) (find(V.begin(), V.end(), X) != V.end())

unsigned int
Word::get_matches(const vector<string>& t) const {
	unsigned int num = 0;
	for (auto& trigram : t) {
		if (CONTAINS(trigrams_, trigram)) {
			num += 1;
		}
	}
	return num;
}

vector<string>
Word::unique_trigrams(const string& word)
{
	vector<string> trigrams;
	if (word.length() == 1 || word.length() == 2) {
		return trigrams;
	}
	for (unsigned long i = 0; i < word.length() - 3; ++i) {
		string trigram(word.substr(i, 3));
		if (!CONTAINS(trigrams, trigram)) {
			trigrams.push_back(trigram);
		}
	}
	sort(trigrams.begin(), trigrams.end());
	return trigrams;
}

vector<string>
Word::unique_trigrams(const Word& word)
{
	vector<string> trigrams;
	string w = word.get_word();
	if (w.length() == 1 || w.length() == 2) {
		return trigrams;
	}
	for (unsigned long i = 0; i < w.length() - 3; ++i) {
		string trigram(w.substr(i, 3));
		if (!CONTAINS(trigrams, trigram)) {
			trigrams.push_back(trigram);
		}
	}
	sort(trigrams.begin(), trigrams.end());
	return trigrams;
}

