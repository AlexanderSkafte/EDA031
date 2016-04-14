#include "client.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include "server.h"
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

map<int, string> options = {
    {Protocol::COM_LIST_NG,    "List newsgroups"},
    {Protocol::COM_CREATE_NG,  "Create newsgroups"},
    {Protocol::COM_DELETE_NG,  "Delete newsgroup"},
    {Protocol::COM_LIST_ART:   "List articles in a newsgroup"},
    {Protocol::COM_CREATE_ART, "Write article"},
    {Protocol::COM_DELETE_ART, "Delete Article"},
    {Protocol::COM_GET_ART,    "Read articles in a newsgroup"},
};

void
client::menu()
{
    cout << "Options:\n"
    for (const auto& entry : options) {
        cout << entry.first << ": " << entry.second << "\n"
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2 || argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number." << e.what() << endl;
		exit(1);
	}

	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed." << endl;
		exit(1);
	}

	client db;

	cout << "Server running" << endl;

	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				unsigned char ch = conn->read();
				MessageHandler mh(conn);

				switch (ch) {

		        case Protocol::COM_LIST_NG:
		            db.listNewsgroups();
		            break;

		        case Protocol::COM_CREATE_NG:
		            db.createNewsgroup(mh);
		            break;

		        case Protocol::COM_DELETE_NG:
		            db.deleteNewsgroup(mh);
		            break;

		        case Protocol::COM_LIST_ART:
		            db.listArticles(mh);
		            break;

		        case Protocol::COM_GET_ART:
		            db.readArticle(mh);
		            break;

		        case Protocol::COM_CREATE_ART:
		            db.createArticle(mh);
		            break;

		        case Protocol::COM_DELETE_ART:
		            db.deleteArticle(mh);
		            break;

		        default:
		            cerror << "Choice does not exist." << endl;
		            exit(1);
		        }
	    	} catch (connectionclosedexception&) {
	    		server.deregisterConnection(conn);
	    		cout << "closed client connection"<< endl;
	    	}
        } else {
        	conn = make_shared<Connection>();
        	server.registerConnection(conn);
        	cout << "Opened connection with a new client" << endl;
        }
	}
}
