#include "Client.h"


Client::Client(SOCKET sock)
{
	this->_sock = sock;
	this->_id = "";
}

Client::Client(SOCKET scok, std::string id)
{
	this->_sock = scok;
	this->_id = id;
}

Client::~Client()
{
}

SOCKET Client::getSocket()
{
	return this->_sock;
}

std::string Client::getId()
{
	return this->_id;
}

void Client::send(std::string message)
{
	Helper::sendData(_sock, message);
}
