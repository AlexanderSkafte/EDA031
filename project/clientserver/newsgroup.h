#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <iostream>
#include <string>
#include <vector>
#include "article.h"

class Newsgroup {
public:
	Newsgroup(int id, std::string name);

	int         id();
	std::string name();
	std::string getArticle(const std::string& sought_article) const;
	std::vector<Article> listNewsgroup() const;
	bool		deleteArticle(std::string article_name);
	void        createArticle(Article a);

private:
	std::string name_;
	int id_;
	std::vector<Article> articles_;
};

#endif
