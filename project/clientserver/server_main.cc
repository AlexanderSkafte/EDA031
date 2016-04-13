#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include "client.h"

using namespace std;


void client::menu()
{
    cout << "Options:" << endl << "1: List newsgroups" << endl << "2: Create newsgroup" << endl << "3: Delete newsgroup" << endl << "4: List articles in a newsgroup" << endl << "5: Read articles in a newsgroup" << endl << "6: Write article" << endl << "7: Delete Article" << endl; 
}

int main(int argc, char* argv[]) {
	if (argc != 2 || argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}

	client db;

	cout<<"Server running"<<endl;

	while(true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			unsigned char ch = conn->read();
			MessageHandler mh(conn);


			switch (ch) {
	        case(1):
	            listNewsgroups();
	            break;
	        case(2):
	            cout << "Enter name of new newsgroup:" << endl;
	            cin >> name;
	            createNewsgroup(conn);
	            break;
	        case(3):
	            cout << "Enter name of newsgroup you want to delete:" << endl;
	            deleteNewsgroup(conn);
	            break;
	        case(4):
	            ListArticles();
	            break;
	        case(5):
	            readAtricles();
	            break;
	        case(6):
	            cout << "Enter nae of new Article"<<endl;
	            writeArticle();
	            break;
	        case(7):
	            deleteArticle();
	            break;
	        default: 
	            cerror << "Non existant choise" << endl;
	            exit(1);
	        }
        }
	}
}