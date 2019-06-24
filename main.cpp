#include <stdio.h>
#include <iostream>
#include <exception>
#include <string>

#include "Server.h"
#include "WSAInitializer.h"

#define CURL_STATICLIB
#include "curl/curl.h"
#ifdef _DEBUG
#pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
#pragma comment(lib,"curl/libcurl_a.lib")
#endif // _DEBUG


int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;
	
	
	try
	{
		WSAInitializer WSAInit;
		Server* s = new Server();
		s->server();	
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	
	
	system("PAUSE");
	return 0;
}


