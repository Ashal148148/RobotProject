#pragma once

#include "Server.h"

class User
{
public:
	User(SOCKET socket);
	User(std::string username, SOCKET socket);
	~User();
	void send(std::string msg);
	std::string getUsername();
	SOCKET getSocket();

private:
	std::string _username;
	SOCKET _sock;
};

