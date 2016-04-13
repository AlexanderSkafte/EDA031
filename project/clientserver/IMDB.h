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
		void addArticle(std::string NG, std::string artName);
		std::string deleteArticle(std::string NG, std::string artName);
		std::string addNG(std::string NG);
		std::string deleteNG(std::string NG);
		std::string getArticle(std::string NG, std::string artName);
		std::string getNG(std::string NG); //Lists all arts in NG
	private:
		unordered_map<std::string, Newsgroup> hashmap;
		int NG_id;
		int art_id;

}

#endif
