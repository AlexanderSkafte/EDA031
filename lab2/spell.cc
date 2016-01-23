#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include "dictionary.h"

using namespace std;

int main() {
	Dictionary dict;
	cout << "Ready; enter a word to have it spell checked:" << endl;
	string word;
	cout << "> ";
	while (cin >> word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		if (dict.contains(word)) {
			cout << "Correct." << endl;
		} else {
			vector<string> suggestions = dict.get_suggestions(word);
			if (suggestions.empty()) {
				cout << "Wrong, no suggestions." << endl;
			} else {
				cout << "Wrong. Suggestions:" << endl;
				for (const auto& w : suggestions) {
					cout << "    " << w << endl;
				}
			}
		}
		cout << "> ";
	}
}

