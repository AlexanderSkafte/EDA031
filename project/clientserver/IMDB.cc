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
void IMDB::addArticle(string NG, string artName, string author, string text) {
	Article a(art_id, author, text, artName);
	++art_id;

	auto itr = hashmap.find(NG);
	if (itr == hashmap.end()) {
		Newsgroup newNG(NG_id, NG);
		newNG.addArticle(a);
		hashmap.insert(NG, newNG);
	} else {
		Newsgroup& thisNG = itr->second;
		thisNG.addArticle(a);
	}

	++NG_id;
}

string IMDB::deleteArticle(string NG, string artName) {
	auto itr = hashmap.find(NG);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		return thisNG.deleteArticle(artName);
	}
}

string IMDB::addNG(string NG) {
	if (hashmap.find(NG) != hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup newNG(NG_id, NG);
		++NG_id;
		hashmap.insert(NG, newNG);
	}
}

string IMDB::deleteNG(string NG) {
	auto itr = hashmap.find(NG);
	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		hashmap.erase(itr);
}

string IMDB::getArticle(string NG, string artName) {
	auto itr = hashmap.find(NG);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		string msg = thisNG.getArticle(artName);
		return msg;
}

string IMDB::getNG(string NG) {
	auto itr = hashmap.find(NG);

	if (itr == hashmap.end) {
		//return error msg in protocol
		return "";
	} else {
		Newsgroup thisNG = itr->second;
		string msg = thisNG.getNG();
		return msg;
	}
}
}
