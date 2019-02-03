#pragma once

#include "Helper.h"
#include "User.h"

class User;

class RecievedMessage
{
public:
	RecievedMessage(SOCKET socket, int msgCode, User* user);
	RecievedMessage(SOCKET socket, int msgCode, User* user, std::vector<std::string> values);
	SOCKET getSock();
	User* getUser();
	void setUser(User* user);
	int getMessageCode();
	std::vector<std::string>& getValues();
private:
	SOCKET _sock;
	User* _user;
	int _messageCode;
	std::vector<std::string> _values;
};

