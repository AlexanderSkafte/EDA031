#ifndef IN_MEMORY_DATA_BASE_H
#define IN_MEMORY_DATA_BASE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>

#include "article.h"
#include "newsgroup.h"
#include "database.h"


class InMemoryDataBase : public DataBase {
public:
	InMemoryDataBase();
	~InMemoryDataBase();

	std::vector<std::pair<std::string, unsigned int>>
		listNewsgroups();

	int
		addNewsgroup(
			std::string);

	int
		deleteNewsgroup(
			std::string newsgroup_title);


	std::vector<Article>
		getArticles(
			std::string newsgroup_title);

	void
		addArticle(
			std::string newsgroup_title, std::string article_name,
			std::string author, std::string text);

	int
		deleteArticle(
			std::string newsgroup_title,
			std::string article_name);



	std::string
		getArticle(
			std::string newsgroup_title,
			std::string article_name);


private:
	std::map<std::string, Newsgroup> hashmap;
	int newsgroup_id;
	int article_id;
};

#endif
