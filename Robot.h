#pragma once

#include "Client.h"

class Robot : Client
{
public:
	static Robot* getInstance();
	virtual void send(std::string message) override;

	~Robot();

	//ensuring the signleton is safe
	Robot(Robot const&) = delete;
	void operator=(Robot const&) = delete;

private:
	Robot();
	std::string _id;



};