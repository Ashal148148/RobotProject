#include "DataBase.h"



DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}

bool DataBase::isUserExists(std::string username)
{
	return false;
}

bool DataBase::addNewUser(std::string email, std::string password)
{
	return false;
}

bool DataBase::isUserAndPassMatch(std::string username, std::string password)
{
	return false;
}

bool DataBase::isEmailExists(std::string email)
{
	return false;
}

void DataBase::resetPassword(std::string newPassword, std::string email)
{
}
