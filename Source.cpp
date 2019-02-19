#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <thread>
#include <string>
#include <Ws2tcpip.h>

#include "WSAInitializer.h"
#include "Protocol.h"
#include "Helper.h"

int main()
{
	WSAInitializer WSAInit;
	SOCKET _sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if (_sock == INVALID_SOCKET)
	{
		printf("\n Socket creation error \n");
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
	}
	try
	{		
		if (connect(_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
			printf("\nConnection Failed \n");
		}
		Helper myH;
		myH.sendData(_sock, "Hello!");
		int bytesNum = 1024;//TODO-- NEED TO EXPECT SIZE AND NOT... BLABLA (4)
		char* data = new char[bytesNum + 1];
		int res = recv(_sock, data, bytesNum, 0);

		if (res == INVALID_SOCKET)
		{
			std::string s = "Error while recieving from socket: ";
			s += std::to_string(_sock);
			throw std::exception(s.c_str());
		}
		data[bytesNum] = '0';
		for (int i = 0; i < 20; i++)
		{
			std::cout  << bytesNum << "    " << i <<"    " << data[i] << std::endl;
		}		
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	::closesocket(_sock);
	system("PAUSE");
	return 0;
}