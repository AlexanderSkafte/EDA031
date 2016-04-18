#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
	Article(std::string author, std::string text, std::string title);
	Article(int art_id, std::string author, std::string text, std::string title);
	int         art_id();
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
