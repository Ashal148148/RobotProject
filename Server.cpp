#include "Server.h"

Server::Server()
{
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_socket == INVALID_SOCKET)
		throw std::exception("ERROR: Building socket failed.");

}

Server::~Server()
{
	for (std::map<SOCKET, User*>::iterator it = _connectedUsers.begin(); it != _connectedUsers.end(); it++)
		delete it->second;

	while (!_queRcvMessages.empty())
	{
		delete _queRcvMessages.front();
		_queRcvMessages.pop();
	}

	::closesocket(_socket);
}

void Server::server()
{
	bindAndListen();
	while (true)
	{
		std::cout << "=========================================" << std::endl;
		std::cout << "[INFO] - Waiting for client connection request" << std::endl;
		std::cout << "=========================================" << std::endl;
		accept();
	}
}

void Server::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception("ERROR: bind failed.");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception("ERROR: listen bind.");

	std::cout << "=========================================" << std::endl;
	std::cout << "[INFO] - Listening on port " << PORT << std::endl;
	std::cout << "=========================================" << std::endl;
}

void Server::accept()
{
	SOCKET clientSocket = ::accept(_socket, NULL, NULL);

	if (clientSocket == INVALID_SOCKET)
		throw std::exception("Error: Accepting socket failed.");

	std::cout << "=========================================" << std::endl;
	std::cout << "Client accepted - socket: " << clientSocket << std::endl;
	std::cout << "=========================================" << std::endl;

	std::thread recievedMessageThread(&Server::handleRecievedMessages, this);
	recievedMessageThread.detach();

	std::thread clientThread(&Server::clientHandler, this, clientSocket);
	clientThread.detach();
}

void Server::clientHandler(SOCKET clientSocket)
{
	while(true)
	{
		RecievedMessage* msg = buildRecievedMessage(clientSocket);
		if (msg == nullptr)
		{
			_mtxRecievedMessages.lock();
			std::cout << "=========================================" << std::endl;
			std::cout << "[IMPORTANT INFO v2] Broke from " __FUNCTION__ " (msg == nullptr) for socket: " << clientSocket << std::endl;
			_mtxRecievedMessages.unlock();

			User* user = getUserBySocket(clientSocket);
			if (user != nullptr)
			{
				_connectedUsers.erase(user->getSocket());
				std::cout << user->getUsername() << " disconnected." << std::endl;
			}
			::closesocket(clientSocket);

			_mtxRecievedMessages.lock();
			std::cout << clientSocket << " disconnected." << std::endl;
			std::cout << "=========================================" << std::endl;
			_mtxRecievedMessages.unlock();

			break;
		}
		addRecievedMessage(msg);
		if (msg->getMessageCode() == FORCED_DISCONNECT)
		{
			_mtxRecievedMessages.lock();
			std::cout << "=========================================" << std::endl;
			std::cout << "[IMPORTANT INFO v2] Broke from " __FUNCTION__ " (msg->getMessageCode() == FORCED_DISCONNECT) for socket: " << clientSocket << std::endl;
			std::cout << "=========================================" << std::endl;
			_mtxRecievedMessages.unlock();
			break;
		}
		if (msg->getMessageCode() == APP_CLOSE)
		{
			_mtxRecievedMessages.lock();
			std::cout << "=========================================" << std::endl;
			std::cout << "[IMPORTANT INFO v2] Broke from " __FUNCTION__ " (msg->getMessageCode() == APP_CLOSE) for socket: " << clientSocket << std::endl;
			std::cout << "=========================================" << std::endl;
			_mtxRecievedMessages.unlock();
			break;
		}
	}
}

void Server::safeDisconnectUser(RecievedMessage* msg)
{
	std::cout << msg->getSock() << " disconnected." << std::endl;
	handleUserSignout(msg);

	::closesocket(msg->getSock());
}

User * Server::handleUserSignin(RecievedMessage* msg)
{
	try
	{
		std::vector<std::string>& values = msg->getValues();
		if (values.size() != 2)
		{
			throw std::exception("invalid arguments amount");
		}
		if (_db.isUserAndPassMatch(values[USERNAME], values[PASSWORD]))
		{
			if (getUserByName(values[USERNAME]) == nullptr)
			{
				Helper::sendData(msg->getSock(), std::to_string(SIGN_IN_SUCCESS));
				return new User(values[USERNAME], msg->getSock());
			}
			else
			{
				Helper::sendData(msg->getSock(), std::to_string(SIGN_IN_FAIL_USER_ALREADY_CONNECTED));
				return nullptr;
			}
		}
		Helper::sendData(msg->getSock(), std::to_string(SIGN_IN_FAIL));
		return nullptr;
	}
	catch (std::exception e)
	{
		std::cout << "Exception thrown in " __FUNCTION__ ": " << e.what() << std::endl;
		Helper::sendData(msg->getSock(), std::to_string(SIGN_IN_FAIL));
		return nullptr;
	}
}

bool Server::handleUserSignup(RecievedMessage* msg)
{
	try
	{
		std::vector<std::string>& values = msg->getValues();
		
		if (values.size() != 3)
		{
			throw std::exception("invalid arguments amount");
		}
		if (Validator::isPasswordValid(values[PASSWORD]) && Validator::isEmailValid(values[EMAIL]))
		{
			if (Validator::isEmailValid(values[EMAIL]))
			{
				if (getUserByName(values[USERNAME]) == nullptr)
				{
					try
					{
						if (_db.addNewUser(values[EMAIL], values[PASSWORD]))
						{
							Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_SUCCESS));
							return true;
						}
						else
						{
							Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL));
							std::cout << values[EMAIL] << " is already exists in the database." << std::endl;
						}
					}
					catch (std::exception& e)
					{
						Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL));
						std::cout << e.what() << std::endl;
					}
				}
				else
				{
					Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL));
					std::cout << values[EMAIL] << " is connected." << std::endl;
				}
			}
			else
			{
			    Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL_EMAIL_INVALID));
				std::cout << values[USERNAME] << " is invalid." << std::endl;
			}
		}
		else
		{
			Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL_PASS_ILLEGAL));
			std::cout << "password is invalid." << std::endl;
		}
		return false;
	}
	catch (std::exception e)
	{
		std::cout << "Exception thrown in handleUserSignUp: " << e.what() << std::endl;
		Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL));
		return false;
	}

	Helper::sendData(msg->getSock(), std::to_string(SIGN_UP_FAIL));
	return false;
}

void Server::handleUserSignout(RecievedMessage* msg)
{
	User* user = getUserBySocket(msg->getSock());
	if(user != nullptr)
	{
		_connectedUsers.erase(user->getSocket());
		std::cout << user->getUsername() << " disconnected." << std::endl;
	}
}


void Server::handleRecievedMessages()
{
	std::unique_lock<std::mutex> lock(_mtxRecievedMessages);

	while (true)
	{
		while (_queRcvMessages.empty())
		{
			_cv.wait(lock);
		}

		RecievedMessage* msg = _queRcvMessages.front();
		_queRcvMessages.pop();

		User* user = nullptr;
		bool flag;
		bool flagToBreak = false;

		_mtxHandleRecivedMessages.lock();
		std::cout << "=========================================" << std::endl;
		std::cout << __FUNCTION__ ": msgCode = " << msg->getMessageCode() << ", client_socket: " << msg->getSock() << std::endl;
		_mtxHandleRecivedMessages.unlock();
		try
		{
			switch (msg->getMessageCode())
			{
			case SIGN_IN:
				user = handleUserSignin(msg);
				if (user != nullptr)
				{
					_connectedUsers[user->getSocket()] = user;
					std::cout << "Adding new user to connected users list: socket = " << user->getSocket() << ", username = " << user->getUsername() << std::endl;
				}
				break;
			case SIGN_OUT:
				handleUserSignout(msg);
				break;
			case SIGN_UP:
				try
				{
					flag = handleUserSignup(msg);
					std::cout << "handleUserSignup's flag: " << flag << std::endl;
				}
				catch(...) {}
				break;
			case APP_CLOSE:
				safeDisconnectUser(msg);
				flagToBreak = true;
				break;
			case RESET_PASSWORD:///***/*/*/*//*/*/*/*/**/*//* TODO
				flag = _db.isEmailExists(msg->getValues()[0]);
				if (flag)
				{
					_db.resetPassword("123456", msg->getValues()[0]);
					msg->getUser()->send(std::to_string(RESET_PASSWORD_SUCCESS));
				}
				else
				{
					msg->getUser()->send(std::to_string(RESET_PASSWORD_FAIL));
				}
				break;
			case FORCED_DISCONNECT:
				flagToBreak = true;
				safeDisconnectUser(msg);
				break;
			case NO_CODE:
				msg->getUser()->send(std::to_string(NO_CODE));
				throw std::exception(std::string(std::string("Error: Message received was not written by the protocol")).c_str());
				break;
			default:
				msg->getUser()->send(std::to_string(INVALID_CODE));
				throw std::exception(std::string(std::string("Error: code '") + std::to_string(msg->getMessageCode()) + std::string("' is undefined.")).c_str());
				break;
			}
			_mtxHandleRecivedMessages.lock();
			std::cout << "=========================================" << std::endl;
			_mtxHandleRecivedMessages.unlock();

			if (flagToBreak)
			{
				_mtxHandleRecivedMessages.lock();
				std::cout << "=========================================" << std::endl;
				std::cout << "[IMPORTANT INFO v1] - Broke from the main loop in the socket: " << msg->getSock() << std::endl;
				std::cout << "=========================================" << std::endl;
				_mtxHandleRecivedMessages.unlock();
				break;
			}
		}
		catch (std::exception e)
		{
			std::cout << e.what() << std::endl;
		}

		delete msg;
	}
}

void Server::addRecievedMessage(RecievedMessage * msg)
{
	_queRcvMessages.push(msg);
	_cv.notify_all();
}

RecievedMessage * Server::buildRecievedMessage(SOCKET socket)
{
	std::vector<std::string> values;
	Validator validator;
	char buffer[BUFFER_SIZE];
	char* pch;

	int dataRead = recv(socket, buffer, BUFFER_SIZE, 0);
	if (dataRead == -1)
	{
		std::cout << "******" << WSAGetLastError() << std::endl;//////*****************************************************
		return nullptr;
	}
	int msgCode;

	if (dataRead == 0)
	{
		msgCode = FORCED_DISCONNECT;
	}
	else
	{
		buffer[dataRead] = 0;

		pch = strtok(buffer, MSG_SEPARATOR);
		while (pch != NULL)
		{
			values.push_back(pch);
			pch = strtok(NULL, MSG_SEPARATOR);
		}

		if (values.size() > 0)
		{
			if (validator.isNumeric(values[0]))
			{
				msgCode = std::stoi(values[0]);
				values.erase(values.begin());
			}
			else
			{
				msgCode = NO_CODE;
			}
		}
		else
		{
			msgCode = NO_CODE;
		}
	}
	User* user = getUserBySocket(socket);
	if (user != nullptr)
	{
		return new RecievedMessage(socket, msgCode, user, values);
	}
	return new RecievedMessage(socket, msgCode, new User(socket), values);
}

User * Server::getUserByName(std::string username)
{
	for (std::map<SOCKET, User*>::iterator it = _connectedUsers.begin(); it != _connectedUsers.end(); ++it)
	{
		if (username == it->second->getUsername())
		{
			return it->second;
		}
	}
	return nullptr;
}

User * Server::getUserBySocket(SOCKET socket)
{
	std::map<SOCKET, User*>::iterator it = _connectedUsers.find(socket);
	if (it != _connectedUsers.end())
	{
		return it->second;
	}
	return nullptr;
}

