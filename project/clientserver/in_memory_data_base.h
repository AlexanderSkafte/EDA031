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
		createNewsgroup(
			const std::string&);

	int
		deleteNewsgroup(
			const std::string& newsgroup_title);


	std::vector<Article>
		listArticles(
			const std::string& newsgroup_title);

	void
		createArticle(
			const std::string& newsgroup_title, const std::string& article_name,
			const std::string& author, const std::string& text);

	int
		deleteArticle(
			const std::string& newsgroup_title,
			const std::string& article_name);



	std::vector<Article>
		getArticle(
			const std::string& newsgroup_title,
			const std::string& article_name);


private:
	std::vector<Newsgroup> newsgroups;
	int newsgroup_id;
	int article_id;
};

#endif
