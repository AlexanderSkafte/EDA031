#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
using namespace std;

class Article {
public:
	Article(int id, std::string author, std::string text, std::string title);
	int         id();
	Article(string author, string text, string title);
	std::string title() const;
	std::string author() const;
	std::string text() const;
private:
	int id_;
	std::string title_;
	std::string author_;
	std::string text_;
};

#endif
