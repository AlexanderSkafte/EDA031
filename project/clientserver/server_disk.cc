#include "adapter_disk.h"
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

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Usage: server_main port-number" << endl;
		cout << argc << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number." << e.what() << endl;
		exit(1);
	}


	Server server(port);
	if (!server.isReady()) {
		cerr << "Wrong port." << endl;
		exit(1); 
	}
	
	cout << "write the filepath to the root directory"<< endl;
	string line;
	cin >> line;
	cin.ignore();
	AdapterDisk adapter(line);

	cout << "Server running" << endl;

	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				MessageHandler mh(conn);
				unsigned char ch = mh.recvByte();
				

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
