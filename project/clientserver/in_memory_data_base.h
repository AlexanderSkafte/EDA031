#ifndef IN_MEMORY_DATA_BASE_H
#define IN_MEMORY_DATA_BASE_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "database.h"

class Newsgroup;
class Article;

class InMemoryDataBase : public DataBase {
public:
	InMemoryDataBase();
	~InMemoryDataBase();

	void
		addArticle(
			std::string newsgroup_title,
			std::string article_name,
			std::string author,
			std::string text);

	int
		deleteArticle(
			std::string newsgroup_title,
			std::string article_name);

	int
		addNewsgroup(
			std::string newsgroup_title);

	int
		deleteNewsgroup(
			std::string newsgroup_title);

	std::string
			getArticle(
				std::string newsgroup_title,
				std::string article_name);

	std::vector<Article>
		getArticles(
			std::string newsgroup_title);

private:
	std::unordered_map<std::string, Newsgroup> hashmap;
	int newsgroup_id;
	int article_id;
};

#endif
