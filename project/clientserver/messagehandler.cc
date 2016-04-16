#include <string>
#include <memory>
#include "messagehandler.h"
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"

using namespace std;

MessageHandler::MessageHandler(shared_ptr<Connection>& conn) : conn_(conn) {}

void
MessageHandler::sendByte(unsigned char b) // throws ConnectionClosedException
{
	try {
		conn_->write(b);
	} catch (exception& e) {
		throw ConnectionClosedException();
	}
}

void
MessageHandler::sendInt(int value) // throws ConnectionClosedException
{
	unsigned char b = (value >> 24);
	sendByte(b);
	b = (value >> 16);
	sendByte(b);
	b = (value >> 8);
	sendByte(b);
	b = value;
}

void
MessageHandler::sendString(const string& str)
{
	sendByte(Protocol::PAR_STRING);
	sendInt(str.size());
	for (unsigned int i = 0; i < str.size(); ++i) {
		sendByte(str[i]);
	}
}

int
MessageHandler::recvInt() //throws ConnectionClosedException
{
	unsigned char byte1 = recvByte();
	unsigned char byte2 = recvByte();
	unsigned char byte3 = recvByte();
	unsigned char byte4 = recvByte();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}


int
MessageHandler::recvByte() // throws ConnectionClosedException
{
	int code = conn_->read();	
	return code;
}

string
MessageHandler::recvString()
{
	int par = recvByte();
	string str = "";
	if (par != Protocol::PAR_STRING) {
		exit(1);
	} else {
		int n = recvInt();
		for (int i = 0; i < n; i++) {
			str += recvByte();  // Finns det en stringbuilder i C++?
                                // Nej, men man kan använda string streams /Alex
		}
	}
	return str;
}

