#include "protocol.h";

MessageHandler::MessageHandler(std::shared_ptr<Connection>& conn)
    : conn_{conn}
{ }

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
MessageHandler::sendNbr(int value) // throws ConnectionClosedException
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
MessageHandler::sendString(const String& str)
{
	sendByte(Protocol::PAR_STRING);
	sendInt(str.size());
	for (unsigned int i = 0; i < str.size(); ++i) {
		sendByte(s[i]);
	}
}

int
MessageHandler::recvInt() throws ConnectionClosedException
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
	int code = conn_.read();
	if (code == Connection.CONNECTION_CLOSED) {
		throw new ConnectionClosedException();
	}
	return code;
}

std::string
MessageHandler::recvString()
{
	int par = recvByte();
	string str = "";
	if (par != Protocol::PAR_STRING) {
		prinf("Wrong format, not string. exiting");
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

