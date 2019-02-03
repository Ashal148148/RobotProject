#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <iterator>

//Crypto++:
//#include <md5.h>
//#include <hex.h>
//end of Crypto++.

#define GAME_ON_DB 0
#define GAME_ENDED_DB 1
#define GAME_TIME_UNDEFINED -1

//Personal status:
#define NUM_GAMES 0
#define NUM_RIGHT_ANSWERS 1
#define NUM_WRONG_ANSWERS 2
#define AVG_TIME 3
#define CORRECT "1"
#define WRONG "0"
#define PERSONAL_STATUS_SIZE 4

//Best scores:
#define NUM_OF_BEST_SCORES 3

//Database name:
#define DB_NAME "triviaDB.db"

//Databases table:
#define USERS_TABLE "t_users"


//static std::map<int, std::map<std::string, std::string>> _results;
//static std::map<int, std::vector<std::map<std::string, std::string>>> _personalResults;
//static std::map<std::string, std::vector<std::map<std::string, std::string>>> _bestScoresResults;

class DataBase
{
public:
	DataBase();
	~DataBase();
	bool isUserExists(std::string username);
	bool addNewUser(std::string email, std::string password);
	bool isUserAndPassMatch(std::string username, std::string password);
	bool isEmailExists(std::string email);
	void resetPassword(std::string newPassword, std::string email);
private:

	//TODO- firebase
	//std::string makeHash(const std::string& s);
	//static int callback(void* notUsed, int argc, char** argv, char** colName);
	//static int callbackPersonalStatus(void* notUsed, int argc, char** argv, char** colName);
	//static int callbackBestScores(void* notUsed, int argc, char** argv, char** colName);
};