#include "protocol.h";


class MessageHandler {

	
	MessageHandler(std::shared_ptr<Connection>& conn) : conn(this.conn) {
	}

	int MessageHandler::readC	ode() {
		int code = readByte();
		return code;
	}

	void MessageHandler::sendByte(unsigned char b) throws ConnectionClosedException {
		try {
			conn -> write(b);
		} catch (exception& e) {
			throw ConnectionClosedException();
		}
	}

	
	void  MessageHandler::sendNbr(int value) throws ConnectionClosedException {
		unsigned char b = (value >> 24);
		sendByte(b);
		b = (value >> 16);
		sendByte(b);
		b = (value >> 8);
		sendByte(b);
		b = value;
	}

	void sendString(const String& str) {
		//KOlla rätt protocol, char c = protocol.något
		sendByte(c);
		sendInt(str.size());
		for (unsigned int i = 0; i<str.size(); i++) {
			sendByte(s[i]);
		}
	}

	int MessageHandler::recvInt() throws ConnectionClosedException {
		unsigned char byte1 = recvByte();
		unsigned char byte2 = recvByte();
		unsigned char byte3 = recvByte();
		unsigned char byte4 = recvByte();
		return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
	}


	int  MessageHandler::recvByte() throws ConnectionClosedException {
		int code = conn.read();
		if (code == Connection.CONNECTION_CLOSED) {
			throw new ConnectionClosedException();
		}
		return code;
	}

	std::string MessageHandler::recvString() {
		int par = readCode();
		string str = "";
		if () {
			//Kolla om det är en string parameter eller något?
		} else {
			int n = readInt();
			for (int i = 0; i<n; i++) {
				s += readByte(); //Finns det en stringbuilder i C++?
			}
		}
		return s;
	}
};
