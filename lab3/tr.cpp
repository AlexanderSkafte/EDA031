
#include <iostream>
#include <sstream>
#include <string>
#include "tr.hpp"

// #define DEBUG(X) // Not debugging
#define DEBUG(X) X // Debugging

#define REDB "\033[1;31m"
#define REDE "\033[0m"

using namespace std;

TagRemover::TagRemover(istream& input)
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
TagRemover::print(ostream& output) const
{
	DEBUG(cout << REDB "--- Printing parsed HTML:" REDE "\n" << endl);
	output << html_ << endl;
	DEBUG(cout << "\n" REDB "--- Print complete." REDE "\n" << endl);
}

void
TagRemover::remove_tags()
{
	size_t beg;
	while ((beg = html_.find("<")) != string::npos) {
		size_t end = html_.find(">");
		html_.erase(beg, end - beg + 1);
	}

	for (auto& p : entities) {
		string entity = p.first;
		string character = p.second;
		size_t i;
		while ((i = html_.find(entity)) != string::npos) {
			html_.replace(i, entity.length(), character);
		}
	}
}

