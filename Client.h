#pragma once

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

#include "Helper.h"

class Client
{
public:
	Client(SOCKET sock);
	Client(SOCKET scok, std::string id);
	~Client();
	SOCKET getSocket();
	std::string getId();
	void send(std::string message);

protected:
	SOCKET _sock;
	std::string _id;
};

