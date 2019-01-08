#include "Server.h"



Server::Server()
{
}

void Server::run()
{
	int sockfd;
	if(sockfd = socket(AF_INET, SOCK_STREAM, 0);//Protocol value for Internet Protocol is 0.
	{
		cout << "Failed to define the socket" << endl;//https://www.geeksforgeeks.org/socket-programming-cc/
	}
}


Server::~Server()
{
}
