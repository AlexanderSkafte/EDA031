#ifndef IN_MEMORY_DATA_BASE_H
#define IN_MEMORY_DATA_BASE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "database.h"

class Newsgroup;
class Article;

class InMemoryDataBase : public DataBase {
public:
	InMemoryDataBase();
	~InMemoryDataBase();

	vector<pair<string, unsigned int>>
		InMemoryDataBase::listNewsgroups();

	int
		createNewsgroup(
			const std::string& newsgroup_name);

	int
		deleteNewsgroup(
			const std::string& newsgroup_name);

	std::vector<Article>
		listArticles(
			const std::string& newsgroup_name);

	void
		createArticle(
			const std::string& newsgroup_name,
			const std::string& article_title,
			const std::string& author,
			const std::string& text);

	int
		deleteArticle(
			const std::string& newsgroup_name,
			const std::string& article_title);

	std::string
		getArticle(
			const std::string& newsgroup_name,
			const std::string& article_title);

private:
	std::unordered_map<std::string, Newsgroup> hashmap;
	int newsgroup_id;
	int article_id;
};

#endif
