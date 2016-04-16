#include <iostream>
#include <vector>
#include <utility>
#include "in_memory_data_base.h"
#include "protocol.h"

using namespace std;

InMemoryDataBase::InMemoryDataBase()
	: newsgroup_id{ 0 }
	, article_id{ 0 }
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
	for (auto& ng : newsgroups) {
		vec.push_back(make_pair(ng.name(), ng.id()));
	}
	return vec;
}

/*Om NG inte finns -> skapa NG. Inga fel ska kunna ske här*/
void
InMemoryDataBase::addArticle(std::string newsgroup_title, std::string article_name,
	std::string author, std::string text)
{
	bool check = false;
	Article a(article_name, author, text);
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			check = true;
			it->addArticle(a);
			break;
		}
	}
	if (!check) {
		Newsgroup ng(newsgroup_id, newsgroup_title);
		ng.addArticle(a);
		newsgroups.push_back(ng);

	}
	++newsgroup_id;
	
}

int
InMemoryDataBase::deleteArticle(string newsgroup_title, string article_name)
{
	bool check = false;
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			if (it->deleteArticle(article_name)) {
				check = true;
				break;
			}
			
		}
	}
	if (!check) {
		//return error msg in protocol
		return Protocol::ERR_ART_DOES_NOT_EXIST;
	}
	else {
		return Protocol::ANS_ACK;
	}
}

int
InMemoryDataBase::addNewsgroup(string newsgroup_title)
{
	bool check = false;
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			check = true;
			break;
		}
	}
	if (check) {
		//return error msg in protocol
		return Protocol::ERR_NG_ALREADY_EXISTS;
	}
	else {
		Newsgroup ng(newsgroup_id, newsgroup_title);
		++newsgroup_id;
		newsgroups.push_back(ng);
		return Protocol::ERR_NG_DOES_NOT_EXIST;
	}
}

int
InMemoryDataBase::deleteNewsgroup(string newsgroup_title)
{
	
	bool check = false;
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			check = true;
			newsgroups.erase(it);
			break;
		}
	}
	if (!check) {
		//return error msg in protocol
		return Protocol::ERR_NG_DOES_NOT_EXIST;
	}
	else {
		return Protocol::ANS_ACK;
	}
}

string
InMemoryDataBase::getArticle(string newsgroup_title, string article_name)
{
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			string text = it->getArticle(article_name);
			if (text.compare("") != 0) {
				return text;
			} 
		}
	}
	return "";
}

vector<Article>
InMemoryDataBase::getArticles(string newsgroup_title)
{
	vector<Article> vec;
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			vec = it->listNewsgroup();
			return vec;
		}
	}
	return vec;
}
