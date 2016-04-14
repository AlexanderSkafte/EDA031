#include "protocol.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "How to use the client: client hostname port"<< endl;
		exit(1);
	}

	int port = 0;

	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Invalid port. " << e.what << endl;
		exit(1);
	}


	Connection conn(argv[1], port);

	if (!conn.isConnected()) {
		cerr << "Connection failed" << endl;
		exit(1);
	}

	cout << "Connection established" <<endl;

	auto ptr = shared_ptr<Connection>(&conn);
	MessageHandler mh(ptr);
	try {
		string line;
		// print alternativen
		while (getline(cin, line)) {
			//print alternativen
			int command = parse_command(line);
			mh.sendInt(command);
			switch (command) {

			case Protocol::COM_LIST_NG:
				list_ng(mh);
				break;
			case Protocol::COM_CREATE_NG:
				createNewsgroup(mh);
				break;
			case Protocol::COM_DELETE_NG:
				deleteNewsgroup(mh);
				break;
			case Protocol::COM_LIST_ART:
				listArt(mh);
				break;
			case Protocol::COM_CREATE_ART:
				createArt(mh);
				break;
			case Protocol::COM_DELETE_ART:
				deleteArt(mh);
				break;
			case Protocol::COM_GET_ART:
				getArt(mh);
				break;
			case: Protocol::COM_END:
				cout<< "Exiting" << endl;
				exit(0);
			default:
				cout<< "Invalid command" << endl;
				break;
			}


		}
	} catch (ConnectionClosedException&) {
		cout << "The server is not responding" << endl;
		exit(1);
	}
}

int parse_command(string line) {
	stringstream ss(line);
	int command;
	try {
		ss >> command;
	} catch (exception&) {
		cerr << "Invalid command, enter a number. Exiting" << endl;
		exit(1);
	}
	return command;
}

void list_ng(MessageHandler mh) {
	unsigned char c = mh.recvByte();
	if (c == Protocol::ANS_NAK) {
		mh.recvByte();
		cout << "No newsgroups are created yet" << endl;
	} else if (c == Protocol::ANS_ACK) {
		unsigned int s = mh.recvInt();
		for (unsigned int i = 0; i<s; ++i) {
			cout << mh.recvString() << " " << mh.recvInt() << endl;
		}
		mh.recvByte();
	}
}

void createNewsgroup(MessageHandler mh) {
	cout << "Name of the new Newsgroup?" << endl;
	string name;
	cin >> name;
	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(name);
	unsigned char resp = mh.recvByte();
	if (resp ==Protocol::ANS_ACK) {
		cout << "The newsgroup was added to the database" << endl;
	} else if (resp == Protocol::ANS_NAK) {
		cout << "The newsgroup already existed" << endl;
	} else {
		//error?
	}
	mh.recvByte();
}

void deleteNewsgroup(MessageHandler mh) {
	cout << "Name of the new Newsgroup?" << endl;
	string name;
	cin >> name;
	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(name);

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_ACK) {
		cout << "Newsgroup was deleted" << endl;
	} else if (resp == Protocol::ANS_NAK) {
		cout << "Error, no newsgroup have that name" << endl;
	} else {
		//error?
	}

	mh.recvByte();
}

void listArticles(MessageHandler mh) {
	cout << "Name of the Newsgroup?" << endl;
	string name;
	cin >> name;
	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(name);

	unsigned char resp = mh.recvByte();
	unsigned int size = mh.recvInt();

	if (resp == Protocol::ANS_NAK) {
		cout << "Error, either the newsgroup is empty or it does not exist" << endl;
	} else if (resp == Protocol::ANS_NAK) {
		for (unsigned int i = 0; i<size; ++i) {
			cout << mh.recvString() << " " << mh.recvInt() << endl;
		}
	}
	mh.recvByte();
}

void createArticle(MessageHandler mh) {
	cout << "Name of the new Newsgroup?" << endl;
	string news_n;
	cin >> news_n;
	cout << "Name of the title?" << endl;
	string title;
	cin >> title;
	cout << "Name of the author?" << endl;
	string aut;
	cin >> aut;
	cout << "Article text" << endl;
	string text;
	cin >> text;

	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(news_n);
	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(title);
	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(aut);
	mh.sendByte(Protocol::PAR_STRING);
	mh.sendString(text);

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_ACK) {
		cout << "Article was created" << endl;
	} else if (resp == Protocol::ANS_NAK) {
		cout << "Article and Newsgroup was created" << endl;
	} else {
		//error?
	}

	mh.recvByte();
}

void deleteArticle(MessageHandler mh) {

}


void getArticle(MessageHandler mh) {
	cout << "Name of the Newsgroup?" << endl;
	string news_n;
	cin >> news_n;
	cout << "Name of the Artcle?" << endl;
	string title;
	cin >> title;

	unsigned char resp = mh.recvByte();
	if (resp == Protocol::ANS_NAK) {
		cout << "No such article/newsgroup" << endl;
	} else if (resp == Protocol::ANS_ACK) {
		cout << "Here is the text: " << mh.recvString() << endl;
	} else {
		//error?
	}
	mh.recvByte();

}
