#include<iostream>
#include "inmemory_db.h"

using namespace std;

inmemory_db::inmemory_db() {
	NG_id = 0;
	art_id = 0;
}

inmemory_db::~inmemory_db() {
	delete hashmap;

}
vector<pair<string, unsigned int>> 
inmemory_db::listNewsgroups()) {
	vector<pair<string, unsigned int>> vec;
    for(auto ng: newsgroups){
        vec.push_back(make_pair(ng.name(), ng.id()));
    }
    return vec;
}



/*Om NG inte finns -> skapa NG. Inga fel ska kunna ske här*/
int 
inmemory_db::addArticle(string newsgroup_title, Article a); 
{
	

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
	return Protocol::ERR_ART_DOES_NOT_EXIST;
}

int 
inmemory_db::deleteArticle(string newsgroup_title, string article_name) 
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

int 
inmemory_db::addNewsgroup(string newsgroup_title) 
{
	if (hashmap.find(newsgroup_title) != hashmap.end) {
		//return error msg in protocol
		return Protocol::ERR_NG_ALREADY_EXISTS;
	} else {
		Newsgroup newNG(newsgroup_id, newsgroup_title);
		++newsgroup_id;
		hashmap.insert(newsgroup_title, newNG);
		return ERR_NG_ALREADY_EXISTS
	}
}

int 
inmemory_db::deleteNewsgroup(string newsgroup_title) 
{
	auto itr = hashmap.find(newsgroup_title);
	if (itr == hashmap.end) {
		//return error msg in protocol
		return Protocol::ERR_NG_DOES_NOT_EXIST;
	} else {
		hashmap.erase(itr);
		return Protocol::ANS_ACK;
	}
}

string 
inmemory_db::getArticle(string newsgroup_title, string article_name) 
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

vector<Article>
inmemory_db::getArtcles(string newsgroup_title) 
{
	vector<Article> vec;
	auto itr = hashmap.find(newsgroup_title);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return vec;
	} else {
		vec = hashmap[itr].listNewsgroups();
		return vec;
	}
}


