#include "User.h"

User::User(SOCKET socket) : Client(socket)
{
	this->_authority = GUEST_AUTH;
	this->_email = "";
}

User::User(std::string email, SOCKET socket) : Client(socket)
{
	this->_authority = USER_AUTH;
	this->_email = email;

}

User::User(std::string email, SOCKET socket, int authority) : Client(socket)
{
	this->_authority = authority;
	this->_email = email;
}

User::User(std::string email, SOCKET socket, int authority, std::string id) : Client(socket, id)
{
	this->_authority = authority;
	this->_email = email;
}

int User::getAuthority()
{
	return _authority;
}

bool User::setAuthority(int selfAuthority, int setAuthority)//TODO
{
	if (selfAuthority >= TEACHER_AUTH && selfAuthority > setAuthority)
	{
		this->_authority = setAuthority;
		return true;
	}
	return false;
}

void User::setAuthority(int authority)
{
	_authority = authority;
}

std::string User::getEmail()
{
	return _email;
}

void User::setEmail(std::string email)
{
	_email = email;
}

User::~User()
{
}