#include <iostream>
#include "in_memory_data_base.h"

using namespace std;

InMemoryDataBase::InMemoryDataBase()
	: newsgroup_id{0}
	, article_id{0}
{ }

InMemoryDataBase::~InMemoryDataBase()
{
	// delete hashmap;  // Hashmap is not a heap allocated object
						// Since it is just declared as a private member
}

vector<pair<string, unsigned int>>
InMemoryDataBase::listNewsgroups()
{
	vector<pair<string, unsigned int>> vec;
    for (const auto& ng : hashmap) {
        vec.push_back(make_pair(ng.second.name(), ng.second.id()));
    }
    return vec;
}

/*Om NG inte finns -> skapa NG. Inga fel ska kunna ske här*/
void
InMemoryDataBase::addArticle(string newsgroup_title, Article a)
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
	//ska man kolla om artiklen redan finns?
	++newsgroup_id;
	//return Protocol::ERR_ART_DOES_NOT_EXIST;
}

int
InMemoryDataBase::deleteArticle(string newsgroup_title, string article_name)
{
	auto itr = hashmap.find(newsgroup_title);
	if (itr == hashmap.end) {
		//return error msg in protocol
		return Protocol::ERR_ART_DOES_NOT_EXIST;
	} else {
		Newsgroup thisNG = itr->second;
		hashmap.erase(it->);
		return Protocol::ANS_DELETE_ART;
	}
}

int
InMemoryDataBase::addNewsgroup(string newsgroup_title)
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
InMemoryDataBase::deleteNewsgroup(string newsgroup_title)
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
InMemoryDataBase::getArticle(string newsgroup_title, string article_name)
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
InMemoryDataBase::getArticles(string newsgroup_title)
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
