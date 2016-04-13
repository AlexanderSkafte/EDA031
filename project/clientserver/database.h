#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "newsgroup.h"
#include "Article.h"

/*An interface for the Database classes*/
class DataBase {
	public:
		virtual ~DataBase() {} //destructor for inherited class
		virtual void addArticle(std::string newsgroup_title, std::string article_name) = 0;
		virtual void deleteArticle(std::string newsgroup_title, std::string article_name) = 0;
		virtual void addNewsgroup(std::string newsgroup_title) = 0;
		virtual void deleteNewsgroup(std::string newsgroup_title) = 0;
		virtual std::string getArticle(std::string newsgroup_title, std::string article_name) = 0;
		virtual std::string getNewsgroup(std::string newsgroup_title) = 0; //Lists all arts in NG
}

#endif
