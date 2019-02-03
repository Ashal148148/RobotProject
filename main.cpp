#include <stdio.h>
#include <iostream>
#include <exception>

#include "Server.h"
#include "WSAInitializer.h"

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;
	WSAInitializer ini;
	try
	{
		Server s;
		s.server();	
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	
	
	system("PAUSE");
	return 0;
}