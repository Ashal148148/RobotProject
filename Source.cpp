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

	try
	{
		WSAInitializer WSAInit;
		SOCKET _sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		sockaddr_in _addr;
		_addr.sin_family = AF_INET;
		void* buff;
		_addr.sin_addr.s_addr = InetPton(AF_INET,L"127.0.0.1",buff);
		_addr.sin_port = htons(PORT);
		bind(_sock, (SOCKADDR*)&_addr, sizeof(_addr));
		Helper myH;
		myH.sendData(_sock, "Hello!");
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}