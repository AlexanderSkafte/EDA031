#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "newsgroup.h"
#include "Article.h"

/*An interface for the Database classes*/
class DataBase {
	public:
		virtual ~DataBase() {} //destructor for inherited class
		virtual void addArticle(std::string NG, std::string artName) = 0;
		virtual void deleteArticle(std::string NG, std::string artName) = 0;
		virtual void addNG(std::string NG) = 0;
		virtual void deleteNG(std::string NG) = 0;
		virtual std::string getArticle(std::string NG, std::string artName) = 0;
		virtual std::string getNG(std::string NG) = 0; //Lists all arts in NG
}

#endif
