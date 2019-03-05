#pragma once

#include "Client.h"

class Robot : Client
{
public:
	static Robot& getInstance();
	void send(std::string message);

	~Robot();

	//ensuring the signleton is safe
	Robot(Robot const&) = delete;
	void operator=(Robot const&) = delete;

private:
	Robot() : Client() {};
	std::string _id;



};

