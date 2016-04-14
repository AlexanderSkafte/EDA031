#ifndef IMDB_H
#define IMDB_H

#include <iostream>
#include "database.h"
#include <unordered_map>

/*In memory database header file*/
class IMDB : public DataBase {
	public:
		IMDB();
		~IMDB();
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
