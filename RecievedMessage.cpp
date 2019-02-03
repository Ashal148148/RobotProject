#include "RecievedMessage.h"

RecievedMessage::RecievedMessage(SOCKET socket, int msgCode, User* user)
{
	_sock = socket;
	_messageCode = msgCode;
	_user = user;
}

RecievedMessage::RecievedMessage(SOCKET socket, int msgCode, User* user, std::vector<std::string> values)
{
	_sock = socket;
	_messageCode = msgCode;
	_user = user;
	_values = values;
}

SOCKET RecievedMessage::getSock()
{
	return _sock;
}

User * RecievedMessage::getUser()
{
	return _user;
}

void RecievedMessage::setUser(User * user)
{
	_user = user;
}

int RecievedMessage::getMessageCode()
{
	return _messageCode;
}

std::vector<std::string>& RecievedMessage::getValues()
{
	return _values;
}
