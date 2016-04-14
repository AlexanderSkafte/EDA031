#ifndef INMEMORY_DB_H
#define INMEMORY_DB_H

#include <iostream>
#include "database.h"
#include <unordered_map>

/*In memory database header file*/
class inmemory_db : public DataBase {
public:
	inmemory_db();
	~inmemory_db();
	void addArticle(std::string newsgroup_title, std::string article_name, 
			std::string author, std::string text);
	std::string deleteArticle(std::string newsgroup_title, std::string article_name);
	std::string addNewsgroup(std::string newsgroup_title);
	std::string deleteNewsgroup(std::string newsgroup_title);
	std::string getArticle(std::string newsgroup_title, std::string article_name);
	std::string getNewsgroup(std::string newsgroup_title); //Lists all arts in NG

private:
	unordered_map<std::string, Newsgroup> hashmap;
	int newsgroup_id;
	int article_id;
}

#endif

