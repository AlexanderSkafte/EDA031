#include<iostream>
#include "IMDB.h"

using namespace std;

IMDB::IMDB() {
	NG_id = 0;
	art_id = 0;
}

IMDB::~IMDB() {
	delete hashmap;

}

/*Om NG inte finns -> skapa NG. Inga fel ska kunna ske här*/
void 
IMDB::addArticle(string newsgroup_title, string article_name, string author, string text) 
{
	Article a(article_id, author, text, article_name);
	++article_id;

	auto itr = hashmap.find(newsgroup_title);
	if (itr == hashmap.end()) {
		Newsgroup newNG(newsgroup_id, newsgroup_title);
		newNG.addArticle(a);
		hashmap.insert(newsgroup_title, newNG);
	} else {
		Newsgroup& thisNG = itr->second;
		thisNG.addArticle(a);
	}

	++newsgroup_id;
}

string 
IMDB::deleteArticle(string newsgroup_title, string article_name) 
{
	auto itr = hashmap.find(newsgroup_title);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		return thisNG.deleteArticle(article_name);
	}
}

string 
IMDB::addNewsgroup(string newsgroup_title) 
{
	if (hashmap.find(newsgroup_title) != hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup newNG(newsgroup_id, newsgroup_title);
		++newsgroup_id;
		hashmap.insert(newsgroup_title, newNG);
	}
}

string 
IMDB::deleteNewsgroup(string newsgroup_title) 
{
	auto itr = hashmap.find(newsgroup_title);
	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		hashmap.erase(itr);
}

string 
IMDB::getArticle(string newsgroup_title, string article_name) 
{
	auto itr = hashmap.find(newsgroup_title);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		string msg = thisNG.getArticle(article_name);
		return msg;
	}
}

string 
IMDB::getNewsgroup(string newsgroup_title) 
{
	auto itr = hashmap.find(newsgroup_title);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		string msg = thisNG.listNewsgroup();
		return msg;
	}
}


