
#include <iostream>
#include <sstream>
#include <string>
#include "tr.hpp"

// #define DEBUG(X) // Not debugging
#define DEBUG(X) X // Debugging

#define REDB "\033[1;31m"
#define REDE "\033[0m"

using namespace std;

TagRemover::TagRemover(std::istream& input)
{
	string line;
	while (getline(input, line)) {
		html_ += (line + "\n");
	}
	DEBUG(cout << "\n" REDB "--- Got the following HTML:" REDE "\n\n"
			<< html_ << endl);

	remove_tags();
}

void
TagRemover::print(std::ostream& output) const
{
	DEBUG(cout << REDB "--- Printing parsed HTML:" REDE "\n" << endl);
	istringstream iss(text_);
	string line;
	while (getline(iss, line)) {
		output << line << endl;
	}
	DEBUG(cout << "\n" REDB "--- Print complete." REDE "\n" << endl);
}

void
TagRemover::remove_tags()
{
	text_.reserve(html_.length());

	bool write = true;
	for (char& c : html_) {
		if (c == '<')           { write = false; }
		if (write || c == '\n') { text_ += c;    }
		if (*(&c - 1) == '>')   { write = true;  }
	}

	for (auto& p : entities) {
		string entity = p.first;
		string character = p.second;
		size_t i;
		while ((i = text_.find(entity)) != string::npos) {
			text_.replace(i, entity.length(), character);
		}
	}

	text_.shrink_to_fit();
}

