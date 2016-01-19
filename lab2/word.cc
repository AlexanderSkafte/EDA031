#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t)
	: w_{w}
	, t_{t}
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
		if (CONTAINS(t_, trigram)) {
			num += 1;
		}
	}
	return num;
}

// Alternatively, make this static and take a const string& word argument
vector<string>
Word::unique_trigrams() const
{
	vector<string> trigrams;
	if (w_.length() == 1 || w_.length() == 2) {
		return trigrams;
	}
	for (unsigned long i = 0; i < w_.length() - 2; ++i) {
		string trigram(w_.substr(i, 3));
		if (!CONTAINS(trigrams, trigram)) {
			trigrams.push_back(trigram);
		}
	}
	sort(trigrams.begin(), trigrams.end());
	return trigrams;
}

vector<string>
Word::unique_trigrams(const string& word)
{
	vector<string> trigrams;
	if (word.length() == 1 || word.length() == 2) {
		return trigrams;
	}
	for (unsigned long i = 0; i < word.length() - 2; ++i) {
		string trigram(word.substr(i, 3));
		if (!CONTAINS(trigrams, trigram)) {
			trigrams.push_back(trigram);
		}
	}
	sort(trigrams.begin(), trigrams.end());
	return trigrams;
}

