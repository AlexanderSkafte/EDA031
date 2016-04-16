#include <iostream>

#include "adapter.h"
#include "connection.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

Adapter::Adapter()
{ }

void
Adapter::listNewsgroups(MessageHandler& mh)
{
    vector<pair<string, unsigned int>> vec = db.listNewsgroups();
    if (vec.empty()) {
    	mh.sendByte(Protocol::ANS_NAK);
    } else {
    	mh.sendByte(Protocol::ANS_ACK);
    	mh.sendInt(vec.size());
	    for (auto i = vec.begin(); i != vec.end();  ++i) {
	    	mh.sendByte(Protocol::PAR_STRING);
	    	mh.sendString(i->first + " ");
	    	mh.sendInt(i->second);
			mh.sendByte(Protocol::PAR_STRING);
			mh.sendString("\n");
	    }
	}
    mh.sendByte(Protocol::ANS_END);
}

void
Adapter::createNewsgroup(MessageHandler& mh)
{
	string newsgroup_name = mh.recvString();
	unsigned char resp = db.deleteNewsgroup(newsgroup_name);

	if (resp == Protocol::ERR_NG_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_ACK);
	} else if (resp == Protocol::ERR_NG_ALREADY_EXISTS) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
        cout << "Exception kanske?" << endl;
	}

    mh.sendByte(Protocol::ANS_END);
}

void
Adapter::deleteNewsgroup(MessageHandler& mh)
{

    string newsgroup_name = mh.recvString();
    string article_name = mh.recvString();
	unsigned char resp = db.deleteArticle(newsgroup_name, article_name);  // TODO(Alexander -> Mattias) fix pls

	if (resp == Protocol::ERR_NG_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_NAK);
	} else if (resp == Protocol::ANS_ACK) {
		mh.sendByte(Protocol::ANS_ACK);
	} else {
        cout << "Exception kanske?" << endl;
	}

    mh.sendByte(Protocol::ANS_END);
}

void
Adapter::listArticles(MessageHandler& mh){
	string newsgroup = mh.recvString();

	vector<Article> vec = db.getArticles(newsgroup);
	if (vec.empty()) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		mh.sendByte(Protocol::ANS_ACK);
		for (auto i = vec.begin(); i<vec.end(); i++) {
			mh.sendByte(Protocol::PAR_STRING);
			mh.sendString(i->title() + "\n");
		}
	}

	mh.sendByte(Protocol::ANS_END);
}

void
Adapter::createArticle(MessageHandler& mh)
{
	string newsgroup = mh.recvString();
	string title     = mh.recvString();
	string author    = mh.recvString();
	string text      = mh.recvString();
	db.addArticle(newsgroup, title, author, text);
	mh.sendByte(Protocol::ANS_ACK);
	mh.sendByte(Protocol::ANS_END);
}

void
Adapter::deleteArticle(MessageHandler& mh) {
	string newsgroup = mh.recvString();
	string article   = mh.recvString();

	unsigned char resp = db.deleteArticle(newsgroup, article);
	if (resp == Protocol::ERR_ART_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_NAK);
	} else if (resp == Protocol::ANS_ACK) {
		mh.sendByte(resp);
	} else {
        cout << "Borde inte komma hit!" << endl;
	}
	mh.sendByte(Protocol::ANS_END);
}

void
Adapter::getArticle(MessageHandler& mh)
{
	string newsgroup = mh.recvString();
	string article = mh.recvString();

	string result = db.getArticle(newsgroup, article);
	if (result.compare("") == 0) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		mh.sendByte(Protocol::ANS_ACK);
		mh.sendByte(Protocol::PAR_STRING);
		mh.sendString(result);
	}

	mh.sendByte(Protocol::ANS_END);
}
