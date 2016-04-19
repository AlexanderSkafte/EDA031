#include "connection.h"
#include <iostream>
#include <memory>
#include <sstream>
#include "client.h"
#include "protocol.h"
#include "messagehandler.h"
#include <map>
#include <regex>
#include "connectionclosedexception.h"

using namespace std;


//Varför måste dem vara här Alexander?
int 	parse_command	(std::string line);
void    listNewsgroups  (MessageHandler mh);
void    createNewsgroup (MessageHandler mh);
void    deleteNewsgroup (MessageHandler mh);
void    listArticles    (MessageHandler mh);
void    createArticle   (MessageHandler mh);
void    deleteArticle   (MessageHandler mh);
void    getArticle      (MessageHandler mh);
void 	sendCommand		(MessageHandler mh, int command);
map<int, string> options = {
    {Protocol::COM_LIST_NG,    "List newsgroups"},
    {Protocol::COM_CREATE_NG,  "Create newsgroups"},
    {Protocol::COM_DELETE_NG,  "Delete newsgroup"},
    {Protocol::COM_LIST_ART,   "List articles in a newsgroup"},
    {Protocol::COM_CREATE_ART, "Write article"},
    {Protocol::COM_DELETE_ART, "Delete Article"},
    {Protocol::COM_GET_ART,    "Read articles in a newsgroup"},
    {Protocol::COM_END,		   "Exit program"}
};

void
menu()
{
    cout << "Options:\n" << endl;
    for (const auto& entry : options) {
        cout << entry.first << ": " << entry.second << endl;
    }
    cout << endl;
}


int
main(int argc, char* argv[])
{
	if (argc != 3) {
		cout << "usage: client hostname port"<< endl;
		exit(1);
	}

	int port = 0;

	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Invalid port." << e.what() << endl;
		exit(1);
	}
	

	Connection conn(argv[1], port);
	auto ptr = shared_ptr<Connection>(&conn);
	if (!ptr->isConnected()) {
		cout << port << endl;
		cerr << "Connection failed." << endl;
		exit(1);
	}

	cout << "Connection established." <<endl;

	MessageHandler mh(ptr);
	try {
		string line;
		menu();
		while (getline(cin, line)) {

			int command = parse_command(line);
			mh.sendByte(command);
			switch (command) {

			case Protocol::COM_LIST_NG:
				listNewsgroups(mh);
				break;

			case Protocol::COM_CREATE_NG:
				createNewsgroup(mh);
				break;

			case Protocol::COM_DELETE_NG:
				deleteNewsgroup(mh);
				break;

			case Protocol::COM_LIST_ART:
				listArticles(mh);
				break;

			case Protocol::COM_CREATE_ART:
				createArticle(mh);
				break;

			case Protocol::COM_DELETE_ART:
				deleteArticle(mh);
				break;

			case Protocol::COM_GET_ART:
				getArticle(mh);
				break;

			case Protocol::COM_END:
				cout<< "Exiting." << endl;
				exit(0);

			default:
				cout<< "Invalid command." << endl;
				break;
			}

			menu();
		}
	} catch (ConnectionClosedException&) {
		cout << "The server is not responding." << endl;
		exit(1);
	}
}

int
parse_command(string line)
{
	stringstream ss(line);
	int command;
	try {
		ss >> command;
	} catch (exception&) {
		cerr << "Invalid command, enter a number; Exiting." << endl;
		exit(1);
	}
	return command;
}

void
listNewsgroups(MessageHandler mh)
{
	mh.sendByte(Protocol::COM_END);
	unsigned char c = mh.recvByte();
	if (c == Protocol::ANS_NAK) {
		cout << "No newsgroups are created yet." << endl;
	} else if (c == Protocol::ANS_LIST_NG) {
		int s = mh.recvInt();
		for (unsigned int i = 0; i<s; ++i) {
			cout << mh.recvString() << " ";
			cout << mh.recvInt() << endl;//" " << mh.recvInt() << endl;
		}
	}
	//buffer ANS_END
	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}
}

void
createNewsgroup(MessageHandler mh)
{
	cout << "Name of the new Newsgroup?" << endl;
	string newsgroup_name;
	getline(cin, newsgroup_name);
	mh.sendString(newsgroup_name);
	mh.sendByte(Protocol::COM_END);	
unsigned int resp = mh.recvByte();
	if (resp ==Protocol::ANS_ACK) {
		cout << "The newsgroup was added to the database." << endl;;
	} else if (resp == Protocol::ANS_NAK) {
		cout << "The newsgroup already exist." << endl;
	} else {
		//error
	}
	
	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}

}

void
deleteNewsgroup(MessageHandler mh)
{
	cout << "Name of the Newsgroup?" << endl;
	string newsgroup_name;
	getline(cin, newsgroup_name);
	mh.sendString(newsgroup_name);
	mh.sendByte(Protocol::COM_END);

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_ACK) {
		cout << "Newsgroup was deleted." << endl;
	} else if (resp == Protocol::ANS_NAK) {
		cout << "Error, no newsgroup have that name." << endl;
	} else {
		//error?
	}

	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}

}

void
listArticles(MessageHandler mh)
{
	cout << "Name of the Newsgroup?" << endl;
	string newsgroup_name;
	getline(cin, newsgroup_name);
	mh.sendString(newsgroup_name);
	mh.sendByte(Protocol::COM_END);

	unsigned char resp = mh.recvByte();

	if (resp == Protocol::ANS_NAK) {
		cout << "Error, either the newsgroup is empty or it does not exist." << endl;
	} else if (resp == Protocol::ANS_ACK) {
		unsigned int size = mh.recvInt();
		for (unsigned int i = 0; i<size; ++i) {
			cout << "Title: " << mh.recvString() << endl;
			cout <<"Id: " << mh.recvInt() << endl;
		}
	}
	
	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}

}

void
createArticle(MessageHandler mh)
{
	cout << "Name of the Newsgroup?" << endl;
	string news_n;
	getline(cin, news_n);
	cout << "Name of the title?" << endl;
	string title;
	getline(cin, title);
	cout << "Name of the author?" << endl;
	string aut;
	getline(cin, aut);
	cout << "Article text" << endl;
	string text;
	getline(cin, text);

	mh.sendString(news_n);
	mh.sendString(title);
	mh.sendString(aut);
	mh.sendString(text);
	mh.sendByte(Protocol::COM_END);

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_ACK) {
		cout << "Article was created." << endl;
	} else {
		//error?
	}

	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}
}

void
deleteArticle(MessageHandler mh)
{
	cout << "Name of the Newsgroup?" << endl;
	string news_n;
	getline(cin, news_n);
	cout << "Name of the Artcle?" << endl;
	string art;
	getline(cin, art);

	mh.sendString(news_n);
	mh.sendString(art);
	mh.sendByte(Protocol::COM_END);

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_ACK) {
		cout << "Article was deleted." << endl;
	} else if (resp == Protocol::ANS_NAK) {
		cout << "Could not find the article." << endl;
	} else {
		//error?
	}

	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}


}


void
getArticle(MessageHandler mh)
{
	cout << "Name of the Newsgroup?" << endl;
	string news_n;
	getline(cin, news_n);
	cout << "Name of the Article?" << endl;
	string title;
	getline(cin, title);

	mh.sendString(news_n);
	mh.sendString(title);
	mh.sendByte(Protocol::COM_END);

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_NAK) {
		cout << "No such Article/Newsgroup." << endl;
	} else if (resp == Protocol::ANS_ACK) {
		int s = mh.recvInt();
		for (int i = 0; i < s; ++i) {
			cout <<"Id: " <<  mh.recvInt() << endl;
			cout << "Title: " << mh.recvString() << endl;
			cout << "Author: " << mh.recvString() << endl;
			cout << "Text: " << mh.recvString() << endl;
		}
	} else {
		//error?
	}
	
	if (mh.recvByte() != Protocol::ANS_END) {
		//error
	}

}
