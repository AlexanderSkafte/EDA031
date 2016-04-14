#include <iostream>

#include "adapter.h"
#include "connection.h"
#include <iostream>
#include <string>
#include <map>

using namespace protocol;
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
	    for (unsigned int i = vec.begin(); i != vec.end();  ++i) {
	    	mh.sendByte(Protocol::PAR_STRING);
	    	mh.sendString(vec.at(i).first + " ");
	    	mh.sendInt(vec.at(i).second));
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
	unsigned char resp = db.createArticle(id_nbr, a);  // TODO(Alexander -> Mattias) fix pls

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

	Vector<Article> vec = db.getArticles(newsgroup);
	if (vec.empty()) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		mh.sendByte(Protocol::ANS_ACK);
		for (unsigned int i = vec.begin(); i<veg.end(); i++) {
			mh.sendByte(Protocol::PAR_STRING);
			mh.sendString(vec.at(i).title() + "\n");
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
	Article a = new Article(author, text, title);

	unsigned char resp = db.createArticle(newsgroup, a);

	if (resp == Protocol::ERR_ART_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_ACK);
	} else {
		cout << "Borde inte komma hit!" << endl;
	}

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
		mh.sendByte(ANS_NAK);
	} else {
		mh.sendByte(ANS_ACK);
		mh.sendByte(Protocol::PAR_STRING);
		mh.sendString(result);
	}

	mh.sendByte(ANS_END);
}
