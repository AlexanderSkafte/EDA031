#include <stdio>

#include "client.h"
#include "connection.h"
#include <iostream>
#include <string>
#include <map>

using namespace protocol;
using namespace std;

client::client() {
	inmemorydb db = new inmemorydb();
}

vector<pair<string, unsigned int>> 
client::listNewsgroups()
{
    vector<pair<string, unsigned int>> vec;
    for(auto ng: newsgroups){
        vec.push_back(make_pair(ng.getId(), ng.name()));
    }
    return vec;
}

void 
client::createNewsgroup(MessageHandler mh)
{
	string newsgroup_name = mh.recvString();
	unsigned char resp = db.deleteNewsgroup(newsgroup_name);

	if (resp == Protocol::ERR_NG_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_ACK);
	} else if (resp == Protocol::ERR_NG_ALREADY_EXISTS) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		printf("exception kanske?");
	}

    mh.sendByte(Protocol::ANS_END);
}

void 
client::deleteNewsgroup(MessageHandler mh)
{
	
    string newsgroup_name = mh.recvString();
	unsigned char resp = db.addArticle(id_nbr, a);

	if (resp == Protocol::ERR_NG_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_NAK);
	} else if (resp == Protocol::ANS_ACK) {
		mh.sendByte(Protocol::ANS_ACK);
	} else {
		printf("exception kanske?");
	}

    mh.sendByte(Protocol::ANS_END);
}

void 
client::writeArticle(MessageHandler mh)
{
	string news_n = mh.recvString();
	string title = recvString();
	string aut = recvString();
	string text = recvString();
	Article a = new Article(aut, text, title);

	unsigned char resp = db.addArticle(news_n, a);

	if (resp == Protocol::ERR_ART_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_ACK);
	} else {
		printf("borde inte komma hit");
	}

    mh.sendByte(Protocol::ANS_END);
}


void
client::listArticles(MessageHandler mh){
    string news_n = mh.recvString();
}

void 
readArticle(string name)
{
    // liknande funktionen ovan
}

void writeArticle(
