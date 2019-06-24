#pragma once
#define _CRT_SECURE_NO_WARNINGS

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
#include "Client.h"
#include "Robot.h"
#include "Component.h"
#include "User.h"
#include "RecievedMessage.h"
#include "Database.h"
#include "Protocol.h"
#include "Validator.h"
#include "Schedule.h"
#include "curl/curl.h"

//MUST ADD "_CRT_SECURE_NO_WARNINGS" TO THE PROJECT'S "Preprocessor Definitions"!

#define EMAIL 0
#define PASSWORD 1


class RecievedMessage;
class User;
class Client;

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

	void sensorsHandler();
	void resfreshSensors();
	void resreshSensor(int sensor);

	
	void wateringHandler();

	void robotHandler();

	User* getUserByEmail(std::string email);
	User* getUserBySocket(SOCKET socket);

	SOCKET _socket;
	std::map<SOCKET, User*> _connectedUsers;
	DataBase _db;
	Schedule _schedule;
	std::queue<RecievedMessage*> _queRcvMessages;
	std::mutex _mtxRecievedMessages; //hundles users and writing to the console/log in the listen thread
	std::mutex _mtxHandleRecivedMessages; //hundles users and writing to the console/log inside individual threads
	std::mutex _mtxSensors;
	std::mutex _mtxSchedule;
	std::mutex _mtxWatering;
	std::condition_variable _cv;//writing to console/log condition variable
	std::condition_variable _cvSensors;
	std::condition_variable _cvSchedule;
	std::condition_variable _cvWatering;
};