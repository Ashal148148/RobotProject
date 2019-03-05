#pragma once

#include "Client.h"

//Authority levels
#define GUEST 1
#define NORMAL_USER 2
#define AUTHORISED_USED 3
#define ADMIN 4
#define SYSTEM_AUTHORITY 5
#define OWNER 6
#define MANUAL_AUTHORITY 7

class User : Client
{
public:
	User(SOCKET socket);
	User(std::string id, SOCKET socket);
	User(std::string id, SOCKET socket, int authority);
	int getAuthority();
	void setAuthority(int selfAuthority, int setAuthority);
	~User();

private:
	int _authority;
};

