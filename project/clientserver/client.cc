#include <iostream>

#include "client.h"
#include "connection.h"
#include <iostream>
#include <string>
#include <map>

using namespace protocol;
using namespace std;

client::client()
{
	inmemorydb db = new inmemorydb();
}

void
client::listNewsgroups(MessageHandler mh)
{
    vector<pair<string, unsigned int>> vec = db.listNewsgroups();
    if (vec.empty()) {
    	mh.sendByte(Protocol::ANS_NAK);
    } else {
    	mh.sendByte(Protocol::ANS_ACK);
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
client::createNewsgroup(MessageHandler mh)
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
client::deleteNewsgroup(MessageHandler mh)
{
	
    string newsgroup_name = mh.recvString();
	unsigned char resp = db.addArticle(id_nbr, a);

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
        cout << "Borde inte komma hit" << endl;
	}

    mh.sendByte(Protocol::ANS_END);
}


void
client::listArticles(MessageHandler mh){
    string news_n = mh.recvString();

    Vector<Article> vec = db.getArticles(news_n);
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
getArticle(MessageHandler mh)
{
   string news_n = mh.recvString();
   string art_n = mh.recvString();

   string result = db.getArticle(news_n, art_n);
   if (result.compare("") == 0) {
   		mh.sendByte(ANS_NAK);		
   } else {
   		mh.sendByte(ANS_ACK);
   		mh.sendByte(Protocol::PAR_STRING);
   		mh.sendString(result);
   }
   mh.sendByte(ANS_END);
}

