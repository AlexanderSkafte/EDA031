#include <iostream>

#include "adapter_disk.h"
#include "connection.h"
#include "protocol.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

AdapterDisk::AdapterDisk(const std::string& line) : db(line)
{
}

AdapterDisk::~AdapterDisk() {
	
}

void
AdapterDisk::listNewsgroups(MessageHandler& mh)
{
    vector<pair<string, unsigned int>> vec = db.listNewsgroups();

 	 //buffer out the COM_END
    if (mh.recvByte() != Protocol::COM_END) {
    	//error
    	exit(1);
    }
	mh.sendByte(Protocol::ANS_LIST_NG);
	mh.sendInt(vec.size());
    for (pair<string, unsigned int> p : vec) {
    	mh.sendString(p.first);
    	mh.sendInt(p.second);
    }
    mh.sendByte(Protocol::ANS_END);
}

void
AdapterDisk::createNewsgroup(MessageHandler& mh)
{
	string newsgroup_name = mh.recvString();
	unsigned char resp = db.createNewsgroup(newsgroup_name);

	unsigned char test = mh.recvByte(); //buffer out the COM_END
	if (test != Protocol::COM_END) {
		exit(1);
	}
	if (resp == Protocol::ERR_NG_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_ACK);
	} else if (resp == Protocol::ERR_NG_ALREADY_EXISTS) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		//error
	}

    mh.sendByte(Protocol::ANS_END);
}

void
AdapterDisk::deleteNewsgroup(MessageHandler& mh)
{

    string newsgroup_name = mh.recvString();

    unsigned char test = mh.recvByte(); //buffer out the COM_END
	if (test != Protocol::COM_END) {
		exit(1);
	}

	unsigned char resp = db.deleteNewsgroup(newsgroup_name);  // TODO(Alexander -> Mattias) fix pls

	if (resp == Protocol::ERR_NG_DOES_NOT_EXIST) {
		mh.sendByte(Protocol::ANS_NAK);
	} else if (resp == Protocol::ANS_ACK) {
		mh.sendByte(Protocol::ANS_ACK);
	} else {
       	//error
	}

    mh.sendByte(Protocol::ANS_END);
}

void
AdapterDisk::listArticles(MessageHandler& mh){

	string newsgroup = mh.recvString();
	unsigned char test = mh.recvByte(); //buffer out the COM_END
	if (test != Protocol::COM_END) {
		exit(1);
	}
	vector<Article> vec = db.listArticles(newsgroup);
	if (vec.empty()) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		mh.sendByte(Protocol::ANS_ACK);
		mh.sendInt(vec.size());
		for (auto i = vec.begin(); i<vec.end(); i++) {
			mh.sendString(i->title());
		}
	}

	mh.sendByte(Protocol::ANS_END);
}

void
AdapterDisk::createArticle(MessageHandler& mh)
{

	string newsgroup = mh.recvString();
	string title     = mh.recvString();
	string author    = mh.recvString();
	string text      = mh.recvString();

	unsigned char test = mh.recvByte(); //buffer out the COM_END
	if (test != Protocol::COM_END) {
		exit(1);
	}
	db.createArticle(newsgroup, title, author, text);
	
	mh.sendByte(Protocol::ANS_ACK);
	mh.sendByte(Protocol::ANS_END);
}

void
AdapterDisk::deleteArticle(MessageHandler& mh) {
	string newsgroup = mh.recvString();
	string article   = mh.recvString();
	unsigned char test = mh.recvByte(); //buffer out the COM_END
	if (test != Protocol::COM_END) {
		exit(1);
	}

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
AdapterDisk::getArticle(MessageHandler& mh)
{
	string newsgroup = mh.recvString();
	string article = mh.recvString();
	unsigned char test = mh.recvByte(); //buffer out the COM_END
	if (test != Protocol::COM_END) {
		//error
	}


	vector<Article> article_list = db.getArticle(newsgroup, article);
	if (article_list.size() == 0) {
		mh.sendByte(Protocol::ANS_NAK);
	} else {
		mh.sendByte(Protocol::ANS_ACK);
		mh.sendInt(article_list.size());
		for (size_t i = 0; i<article_list.size(); ++i) {
			mh.sendInt(article_list.at(i).art_id());
			mh.sendString(article_list.at(i).title());
			mh.sendString(article_list.at(i).author());
			mh.sendString(article_list.at(i).text());
		}
	}

	mh.sendByte(Protocol::ANS_END);
}
