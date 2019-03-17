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
#include "Singleton.h"

using std::cout;
using std::cin;
using std::endl;

void run1();
void run2();

Singleton * Singleton::instance;
std::mutex Singleton::mutex;
int main()
{
	std::thread run1Thread(&run1);
	std::thread run2Thread(&run2);

	run1Thread.detach();
	run2Thread.detach();

	
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	system("PAUSE");
	return 0;
}

void run1()
{
	Singleton* inst = Singleton::getInstance();
	cout << inst->getNum() << endl;
	inst->setNum(10);
	cout << inst->getNum() << endl;
}

void run2()
{
	Singleton* inst = Singleton::getInstance();
	cout << inst->getNum() << endl;
	inst->setNum(20);
	cout << inst->getNum() << endl;
}

/*
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
for (int j = 0; j < 10; j++)
{
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
data[res] = 0;
std::cout << data << std::endl;
std::this_thread::sleep_for(std::chrono::seconds(3));
}
}
catch (std::exception e)
{
std::cout << e.what() << std::endl;
}
::closesocket(_sock);
*/