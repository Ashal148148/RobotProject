#pragma once

#include "Client.h"

class Robot : public Client
{
public:
	~Robot();
	Robot();


private:
	
	std::string _id;
};
