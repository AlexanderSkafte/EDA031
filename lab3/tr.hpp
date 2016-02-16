#ifndef TAG_REMOVER_H
#define TAG_REMOVER_H

#include <vector>
#include <iostream>

class TagRemover {
public:
	TagRemover(std::istream& input);
	void print(std::ostream& output) const;

private:
	void remove_tags();

	std::string html_;

	std::vector<std::pair<std::string, std::string>> entities = {
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&nbsp;", " "},
		{"&amp;", "&"}
	};
};

#endif

