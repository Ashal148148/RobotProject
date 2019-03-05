#include "User.h"

User::User(SOCKET socket) : Client(socket)
{
	this->_authority = GUEST;
}

User::User(std::string id, SOCKET socket) : Client(socket,id)
{
	this->_authority = GUEST;
}

User::User(std::string id, SOCKET socket, int authority) : Client(socket,id)
{
	this->_authority = authority;
}

int User::getAuthority()
{
	return _authority;
}

void User::setAuthority(int selfAuthority, int setAuthority)//TODO
{

}

User::~User()
{
}



