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

int
InMemoryDataBase::createNewsgroup(const string& newsgroup_name)
{
	if (hashmap.find(newsgroup_name) != hashmap.end()) {
		//return error msg in protocol
		return Protocol::ERR_NG_ALREADY_EXISTS;
	} else {
		Newsgroup newNG(newsgroup_id, newsgroup_name);
		++newsgroup_id;
		hashmap.insert(newsgroup_name, newNG);
        return Protocol::ERR_NG_ALREADY_EXISTS;
	}
}

int
InMemoryDataBase::deleteNewsgroup(const string& newsgroup_name)
{
	auto itr = hashmap.find(newsgroup_name);
	if (itr == hashmap.end()) {
		//return error msg in protocol
		return Protocol::ERR_NG_DOES_NOT_EXIST;
	} else {
		hashmap.erase(itr);
		return Protocol::ANS_ACK;
	}
}

vector<Article>
InMemoryDataBase::listArticles(const string& newsgroup_name)
{
	vector<Article> vec;
	auto itr = hashmap.find(newsgroup_name);
	if (itr == hashmap.end()) {
		//return error msg in protocol
		return vec;
	} else {
		vec = hashmap[itr].listNewsgroups();
		return vec;
	}
}

/*Om NG inte finns -> skapa NG. Inga fel ska kunna ske här*/
void
InMemoryDataBase::createArticle(const string& newsgroup_name,
                                const string& article_title,
                                const string& author,
                                const string& text)
{
	auto itr = hashmap.find(newsgroup_name);
	if (itr == hashmap.end()) {
		Newsgroup newNG(newsgroup_id, newsgroup_name);
		newNG.createArticle(a);
		hashmap.insert(newsgroup_name, newNG);
	} else {
		Newsgroup& thisNG = itr->second;
		thisNG.createArticle(a);
	}
	//ska man kolla om artiklen redan finns?
	++newsgroup_id;
	//return Protocol::ERR_ART_DOES_NOT_EXIST;
}

int
InMemoryDataBase::deleteArticle(const string& newsgroup_name,
                                const string& article_name)
{
	auto itr = hashmap.find(newsgroup_name);
	if (itr == hashmap.end) {
		//return error msg in protocol
		return Protocol::ERR_ART_DOES_NOT_EXIST;
	} else {
		Newsgroup thisNG = itr->second;
        thisNG.deleteArticle(article_name);
		return Protocol::ANS_ACK;
	}
}

string
InMemoryDataBase::getArticle(const string& newsgroup_name,
                             const string& article_name)
{
	auto itr = hashmap.find(newsgroup_name);
	if (itr == hashmap.end()) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		string msg = thisNG.getArticle(article_name);
		return msg;
	}
}
