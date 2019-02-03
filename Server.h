#pragma once

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <queue>
#include <exception>
#include <thread>
#include <vector>
#include <map>
#include <sstream>
#include <mutex>
#include <condition_variable>

#include "Helper.h"
#include "User.h"
#include "RecievedMessage.h"
#include "Database.h"
#include "Protocol.h"
#include "Validator.h"

//MUST ADD "_CRT_SECURE_NO_WARNINGS" TO THE PROJECT'S "Preprocessor Definitions"!
#define USERNAME 0
#define PASSWORD 1
#define EMAIL 2

class RecievedMessage;
class User;

class Server
{
public:
	Server();
	~Server();
	
	void server();
private:
	void bindAndListen();
	void accept();
	void clientHandler(SOCKET clientSocket);
	void safeDisconnectUser(RecievedMessage* msg);

	User* handleUserSignin(RecievedMessage* msg);
	bool handleUserSignup(RecievedMessage* msg);
	void handleUserSignout(RecievedMessage* msg);

	void handleRecievedMessages();
	void addRecievedMessage(RecievedMessage* msg);
	RecievedMessage* buildRecievedMessage(SOCKET socket);

	User* getUserByName(std::string username);
	User* getUserBySocket(SOCKET socket);

	SOCKET _socket;
	std::map<SOCKET, User*> _connectedUsers;
	DataBase _db;
	std::queue<RecievedMessage*> _queRcvMessages;
	std::mutex _mtxRecievedMessages;
	std::condition_variable _cv;

};