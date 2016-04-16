#include "adapter.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include "server.h"
#include "messagehandler.h"
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
    {Protocol::COM_LIST_ART,   "List articles in a newsgroup"},
    {Protocol::COM_CREATE_ART, "Write article"},
    {Protocol::COM_DELETE_ART, "Delete Article"},
    {Protocol::COM_GET_ART,    "Read articles in a newsgroup"}
};

void
menu()
{
    cout << "Options:\n" << endl;
    for (const auto& entry : options) {
        cout << entry.first << ": " << entry.second << "\n";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2 && argc != 3) {
		cerr << "Usage: server_main host-name port-number" << endl;
		cout << argc << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number." << e.what() << endl;
		exit(1);
	}


	Server server(port);
	if (!server.isReady()) {
		cerr << "Wrong port." << endl;
		exit(1); 
	}
	Adapter adapter;

	cout << "Server running" << endl;

	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				unsigned char ch = conn->read();
				MessageHandler mh(conn);

				switch (ch) {

		        case Protocol::COM_LIST_NG:
		            adapter.listNewsgroups(mh);
		            break;

		        case Protocol::COM_CREATE_NG:
		            adapter.createNewsgroup(mh);
		            break;

		        case Protocol::COM_DELETE_NG:
		            adapter.deleteNewsgroup(mh);
		            break;

		        case Protocol::COM_LIST_ART:
		            adapter.listArticles(mh);
		            break;

		        case Protocol::COM_GET_ART:
		            adapter.getArticle(mh);
		            break;

		        case Protocol::COM_CREATE_ART:
		            adapter.createArticle(mh);
		            break;

		        case Protocol::COM_DELETE_ART:
		            adapter.deleteArticle(mh);
		            break;

		        default:
		            cerr << "Choice does not exist." << endl;
		            exit(1);
		        }
	    	} catch (ConnectionClosedException&) {
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
