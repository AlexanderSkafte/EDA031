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
InMemoryDataBase::createArticle(const std::string& newsgroup_title, const std::string& article_name,
	const std::string& author, const std::string& text)
{
	bool check = false;
	++article_id;
	Article a(article_id, author, text, article_name);
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			check = true;
			it->createArticle(a);
			break;
		}
	}
	if (!check) {
		Newsgroup ng(newsgroup_id, newsgroup_title);
		ng.createArticle(a);
		newsgroups.push_back(ng);

	}
	++newsgroup_id;
	
}

int
InMemoryDataBase::deleteArticle(const string& newsgroup_title, const string& article_name)
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
InMemoryDataBase::createNewsgroup(const string& newsgroup_title)
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
InMemoryDataBase::deleteNewsgroup(const string& newsgroup_title)
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

vector<Article>
InMemoryDataBase::getArticle(const string& newsgroup_title, const string& article_name)
{
	vector<Article> all_articles;
	for (auto it = newsgroups.begin(); it!= newsgroups.end(); ++it) {
		if (it->name().compare(newsgroup_title) == 0) {
			vector<Article> article_list = it->getArticle(article_name);
			size_t s = article_list.size();
			if (s != 0) {
				for (size_t i = 0; i<s; ++i) {
					all_articles.push_back(article_list.at(i));
				}
			} 
		}
	}
	return all_articles;
}

vector<Article>
InMemoryDataBase::listArticles(const string& newsgroup_title)
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
