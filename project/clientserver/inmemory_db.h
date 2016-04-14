#ifndef INMEMORY_DB_H
#define INMEMORY_DB_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "database.h"

/*In memory database header file*/
class inmemory_db : public DataBase {
public:
	inmemory_db();
	~inmemory_db();
	void addArticle(std::string newsgroup_title, std::string article_name, 
			std::string author, std::string text);
	int deleteArticle(std::string newsgroup_title, std::string article_name);
	int addNewsgroup(std::string newsgroup_title);
	int deleteNewsgroup(std::string newsgroup_title);
	std::string getArticle(std::string newsgroup_title, std::string article_name);
	std::vector<Article> getArticles(std::string newsgroup_title); //Lists all arts in NG

private:
	std::unordered_map<std::string, Newsgroup> hashmap;
	int newsgroup_id;
	int article_id;
};

#endif

