#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

class MessageHandler {
public:
	MessageHandler(Connection& conn);
	int readCode();

	void sendByte(unsigned char);
	void sendNbr(int nbr);
	void sendString(const std::string&); 
	int recvInt(); 
	int recvByte(); 
	std::string recvString();

private:
	std::shared_ptr<Connection)& conn;
};

#endif 

