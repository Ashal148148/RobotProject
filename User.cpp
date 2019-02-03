#include "User.h"

User::User(SOCKET socket)
{
	_sock = socket;
	_username = "";
}

User::User(std::string username, SOCKET socket)
{
	_username = username;
	_sock = socket;
}

User::~User()
{
}

void User::send(std::string msg)
{
	Helper::sendData(_sock, msg);
}

std::string User::getUsername()
{
	return _username;
}

SOCKET User::getSocket()
{
	return _sock;
}

