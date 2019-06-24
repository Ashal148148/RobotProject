#pragma once

#include "Client.h"

class User : public Client
{
public:
	User(SOCKET socket);
	User(std::string email, SOCKET socket);
	User(std::string email, SOCKET socket, int authority);
	User(std::string email, SOCKET socket, int authority, std::string id);

	int getAuthority();
	bool setAuthority(int selfAuthority, int setAuthority);
	void setAuthority(int authority);
	std::string getEmail();
	void setEmail(std::string email);
	~User();

private:
	int _authority;
	std::string _email;
};
