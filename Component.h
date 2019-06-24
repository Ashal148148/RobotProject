#pragma once
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

#include "Helper.h"
#include "Protocol.h"

class Component
{
public:
	Component();
	Component(int port);
	int getPort();
	~Component();
	static void connectToComponent(Component component);//TODO

private:
	int _port;
};