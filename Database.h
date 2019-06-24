#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

#include "sqlite3.h"

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
#define DB_NAME "greenhouseDB.db"

//Databases table:
#define USERS_TABLE "t_users"
#define CAMERA_TABLE "t_camera"
#define POLLINATION_TABLE "t_pollination"
#define SENSOR1_TABLE "t_sensor1"
#define SENSOR2_TABLE "t_sensor2"
#define SENSOR3_TABLE "t_sensor3"
#define SENSOR4_TABLE "t_sensor4"
#define SENSOR5_TABLE "t_sensor5"
#define SENSOR6_TABLE "t_sensor6"
#define SENSOR7_TABLE "t_sensor7"
#define SENSOR8_TABLE "t_sensor8"


static std::map<int, std::map<std::string, std::string>> _results;
static std::map<int, std::vector<std::map<std::string, std::string>>> _personalResults;
static std::map<std::string, std::vector<std::map<std::string, std::string>>> _bestScoresResults;

class DataBase
{
public:
	DataBase();
	~DataBase();
	bool addNewUser(std::string email, std::string password, int authority);
	bool isUserAndPassMatch(std::string username, std::string password);
	bool isEmailExists(std::string email);
	void resetPassword(std::string newPassword, std::string email);
	void addSensorValue(std::string value, std::string date, std::string time, int sensor);
	void addPollination(std::string date, std::string  time);
	void addPicture(std::string picture, std::string date, std::string time);//picture should be in picture format
	std::string getPicturesTinesInDate(std::string date);
	std::string getPicture(std::string date, std::string time);//return values should be image container
	std::vector<std::string> getPollinationsByDate(std::string date);
	std::vector<std::string> getSensorValuesByDate(std::string date);


private:
	sqlite3* _db;

	//Crypto++
	//std::string makeHash(const std::string& s);
	static int callback(void* notUsed, int argc, char** argv, char** colName);
	static int callbackPersonalStatus(void* notUsed, int argc, char** argv, char** colName);
	static int callbackBestScores(void* notUsed, int argc, char** argv, char** colName);
};