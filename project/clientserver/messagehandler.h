#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>

class MessageHandler {
public:
	MessageHandler(Connection& conn);
	int 			readCode	();
	void			sendByte	(unsigned char);
	void			sendNbr		(int value);
	void			sendString	(const std::string& str);
	int				recvInt		();
	int				recvByte	();
	std::string 	recvString	();

private:
	std::shared_ptr<Connection>& conn_;
};

#endif
