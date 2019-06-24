#include "DataBase.h"



DataBase::DataBase()
{
	int rc = sqlite3_open(DB_NAME, &_db);
	if (rc)
	{
		throw std::exception((std::string("ERROR: Can't open database ") + std::string(sqlite3_errmsg(_db))).c_str());
	}
	//CREATE TABLE IF NOT EXISTS t_sensor1(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL);
	//CREATE TABLE IF NOT EXISTS t_users(id INTEGER PRIMARY KEY AUTOINCREMENT,email TEXT UNIQUE NOT NULL, password TEXT NOT NULL, authority INTEGER NOT NULL);
	//CREATE TABLE IF NOT EXISTS t_camera(picture_id INTEGER PRIMARY KEY AUTOINCREMENT,picture BLOB NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL);
	//CREATE TABLE IF NOT EXISTS t_pollination(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, date TEXT NOT NULL, time TEXT NOT NULL);
	char* zErrMsg;

	std::string query("CREATE TABLE IF NOT EXISTS " + std::string(USERS_TABLE) +  "(id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT UNIQUE NOT NULL, password TEXT NOT NULL, authority INTEGER NOT NULL)");
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	query = "CREATE TABLE IF NOT EXISTS " + std::string(CAMERA_TABLE) + "(picture_id INTEGER PRIMARY KEY AUTOINCREMENT,picture BLOB NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	query = "CREATE TABLE IF NOT EXISTS " + std::string(POLLINATION_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR1_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR2_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR3_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR4_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR5_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR6_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query = "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR7_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
	query =  "CREATE TABLE IF NOT EXISTS " + std::string(SENSOR8_TABLE) + "(entry_num INTEGER PRIMARY KEY AUTOINCREMENT, value TEXT NOT NULL, date TEXT NOT NULL, time TEXT NOT NULL)";
	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
}

DataBase::~DataBase()
{
	sqlite3_close(_db);
}


bool DataBase::addNewUser(std::string email, std::string password, int authority)
{
	//Crypto++
	//email = makeHash(email);
	//password = makeHash(password);
	
	if (isEmailExists(email))
	{
		return false;
	}
	else
	{
		char* zErrMsg;

		std::string query("INSERT INTO " + std::string(USERS_TABLE) + " (email, password, authority) values('" + email + "', '" + password + "', " + std::to_string(authority) + ")");
		//std::cout << query << std::endl;//debug
		int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
			sqlite3_free(zErrMsg);
		}
	}

	return true;
}

bool DataBase::isUserAndPassMatch(std::string user, std::string pass)
{
	/*
	user = makeHash(user);
	pass = makeHash(pass);*/

	std::string query = "SELECT * FROM " + std::string(USERS_TABLE) + " WHERE username = '" + user + "' AND password = '" + pass + "'";
	struct sqlite3_stmt* stmt;

	int result = sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK)
	{
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			sqlite3_finalize(stmt);
			return true;
		}
	}
	sqlite3_finalize(stmt);

	return false;
}

bool DataBase::isEmailExists(std::string email)
{
	std::string query = "SELECT * FROM " + std::string(USERS_TABLE) + " WHERE email = '" + email + "'";
	struct sqlite3_stmt* stmt;

	int result = sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK)
	{
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			sqlite3_finalize(stmt);
			return true;
		}
	}
	sqlite3_finalize(stmt);
	return false;
}

void DataBase::resetPassword(std::string newPassword, std::string email)
{
	_results.clear();
	char* zErrMsg;

	//ewPassword = makeHash(newPassword);

	std::string query = "UPDATE " + std::string(USERS_TABLE) + " SET password = '" + newPassword + "' WHERE email = '" + email + "'";
	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
}

void DataBase::addSensorValue(std::string value, std::string date, std::string time, int sensor)
{
	char* zErrMsg;
	std::string query = "";

	switch (sensor)
	{
	case 1:
		query = ("INSERT INTO " + std::string(SENSOR1_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 2:
		query = ("INSERT INTO " + std::string(SENSOR2_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 3:
		query = ("INSERT INTO " + std::string(SENSOR3_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 4:
		query = ("INSERT INTO " + std::string(SENSOR4_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 5:
		query = ("INSERT INTO " + std::string(SENSOR5_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 6:
		query = ("INSERT INTO " + std::string(SENSOR6_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 7:
		query = ("INSERT INTO " + std::string(SENSOR7_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	case 8:
		query = ("INSERT INTO " + std::string(SENSOR8_TABLE) + " (value, date, time) values('" + value + "', '" + date + "', '" + time + "')");
		break;
	default:
		break;
	}
	
	//std::cout << query << std::endl;//debug
	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

}

void DataBase::addPollination(std::string date, std::string time)
{
	char* zErrMsg;

	std::string query("INSERT INTO " + std::string(POLLINATION_TABLE) + " (date, time) values('" + date + "', '" + time + "')");
	//std::cout << query << std::endl;//debug
	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception((std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}
}

std::string DataBase::getPicture(std::string date, std::string time)
{
	return std::string();
}
/*
std::vector<Question*> DataBase::initQuestion(int questionsNo)
{
	_results.clear();
	std::vector<Question*> toReturn;
	char* zErrMsg;

	std::string query("SELECT * FROM " + std::string(QUESTIONS_TABLE) + " ORDER BY RANDOM() LIMIT " + std::to_string(questionsNo));

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	for (auto it = _results.begin(); it != _results.end(); it++)
	{
		toReturn.push_back(new Question(it->first, it->second["question"], it->second["correct_ans"], it->second["ans2"], it->second["ans3"], it->second["ans4"]));
	}

	return toReturn;
}

int DataBase::insertNewGame()
{
	_results.clear();
	char* zErrMsg;

	std::string query("INSERT INTO " + std::string(GAMES_TABLE) + " (status, start_time, end_time) values('" + std::to_string(GAME_ON_DB) + "', strftime('%Y-%m-%d %H:%M:%S', datetime('now')), '" + std::to_string(GAME_TIME_UNDEFINED) + "')");

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	query = "SELECT * FROM " + std::string(GAMES_TABLE) + " WHERE game_id = (SELECT MAX(game_id) FROM " + std::string(GAMES_TABLE) + ")";

	rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	int idToReturn = _results.begin()->first;

	return idToReturn;
}

bool DataBase::updateGameStatus(int gameID)
{
	_results.clear();
	char* zErrMsg;

	std::string query("UPDATE " + std::string(GAMES_TABLE) + " SET end_time = strftime('%Y-%m-%d %H:%M:%S', datetime('now')), status = " + std::to_string(GAME_ENDED_DB) + " WHERE game_id = " + std::to_string(gameID));

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		return false;
		sqlite3_free(zErrMsg);
	}
	return true;
}

bool DataBase::addAnswerToPlayer(int gameID, std::string username, int questionID, std::string answer, bool isCorrect, int answerTime)
{
	_results.clear();
	char* zErrMsg;
	std::string query("INSERT INTO " + std::string(PLAYERS_ANSWERS) + " (game_id, username, question_id, player_answer, is_correct, answer_time) values('" + std::to_string(gameID) + "', '" + username + "', '" + std::to_string(questionID) + "', '" + answer + "', '" + std::to_string(isCorrect) + "', '" + std::to_string(answerTime) + "')");

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		return false;
		sqlite3_free(zErrMsg);
	}
	return true;
}

int DataBase::getQuestionsCount()
{
	_results.clear();
	char* zErrMsg;
	int toReturn = 0;

	std::string query("SELECT * FROM " + std::string(QUESTIONS_TABLE));

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	toReturn = _results.size();

	return toReturn;
}

std::vector<std::string> DataBase::getPersonalStatus(std::string str)
{
	_personalResults.clear();
	char* zErrMsg;
	std::string query("SELECT * FROM " + std::string(PLAYERS_ANSWERS) + " WHERE username = \'" + str + "\'");

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callbackPersonalStatus, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	std::vector<std::string> toReturn;
	if (_personalResults.size() == 0)
	{
		toReturn.push_back(std::to_string(0));
		toReturn.push_back(std::to_string(0));
		toReturn.push_back(std::to_string(0));
		toReturn.push_back(std::to_string(0));
		return toReturn;
	}

	int numRightAnswers = 0;
	int numWrongAnswers = 0;
	int timeSum = 0;
	int questionsAnswered = 0;

	for (auto it = _personalResults.begin(); it != _personalResults.end(); it++)
	{
		for (auto vecIt = it->second.begin(); vecIt != it->second.end(); vecIt++)
		{
			if ((*vecIt)["is_correct"] == CORRECT)
				numRightAnswers++;
			else
				numWrongAnswers++;

			questionsAnswered++;
			timeSum += std::atoi(((*vecIt)["answer_time"]).c_str());
		}
	}

	double avgTime = timeSum / questionsAnswered;

	/*
	std::cout << "===============DEBUG===============" << std::endl;
	std::cout << "numRightAnswers: " << numRightAnswers << std::endl;
	std::cout << "numWrongAnswers: " << numWrongAnswers << std::endl;
	std::cout << "timeSum: " << timeSum << std::endl;
	std::cout << "questionsAnswered: " << questionsAnswered << std::endl;
	std::cout << "avgTime: " << avgTime << std::endl;
	std::cout << "_personalResults.size(): " << _personalResults.size() << std::endl;
	std::cout << "===============DEBUG===============" << std::endl;
	*

	toReturn.push_back(std::to_string(_personalResults.size()));
	toReturn.push_back(std::to_string(numRightAnswers));
	toReturn.push_back(std::to_string(numWrongAnswers));
	toReturn.push_back(std::to_string(avgTime));

	return toReturn;
}

std::vector<std::string> DataBase::getBestScores()
{
	_bestScoresResults.clear();
	char* zErrMsg;
	std::string query("SELECT * FROM " + std::string(PLAYERS_ANSWERS));

	int rc = sqlite3_exec(_db, query.c_str(), &DataBase::callbackBestScores, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		throw std::exception(std::string(std::string("SQL Error: " + std::string(zErrMsg))).c_str());
		sqlite3_free(zErrMsg);
	}

	std::vector<std::string> toReturn;
	if (_bestScoresResults.size() == 0)
	{
		toReturn.push_back("0  0");
		toReturn.push_back("0  0");
		toReturn.push_back("0  0");
		return toReturn;
	}

	std::map<std::string, int> usernameAndScore;
	for (auto it = _bestScoresResults.begin(); it != _bestScoresResults.end(); it++)
	{
		usernameAndScore[it->first] = 0;
		for (auto vecIt = it->second.begin(); vecIt != it->second.end(); vecIt++)
		{
			if ((*vecIt)["is_correct"] == CORRECT)
				usernameAndScore[it->first]++;
		}
	}

	//switch between the key and the value (because map is sorted by key)
	std::map<int, std::string> usernameAndScoreSorted;
	std::transform(usernameAndScore.begin(), usernameAndScore.end(), std::inserter(usernameAndScoreSorted, usernameAndScoreSorted.begin()), [](const std::pair<std::string, int> &p) {return std::pair<int, std::string>(p.second, p.first); });

	//getting the top 3 scores
	std::vector<int> scores;
	for (auto it = usernameAndScoreSorted.begin(); it != usernameAndScoreSorted.end(); it++)
	{
		scores.push_back(it->first);
	}
	std::sort(scores.begin(), scores.end(), [](int const &a, int const &b) { return a > b; });

	if (scores.size() < NUM_OF_BEST_SCORES)
	{
		int temp = NUM_OF_BEST_SCORES - scores.size();
		for (unsigned int i = 0; i < scores.size(); i++)
		{
			toReturn.push_back(usernameAndScoreSorted[scores[i]] + " " + std::to_string(scores[i]));
		}
		for (int i = 0; i < temp; i++)
		{
			toReturn.push_back("0  0");
		}
	}
	else
	{
		for (int i = 0; i < NUM_OF_BEST_SCORES; i++)
		{
			toReturn.push_back(usernameAndScoreSorted[scores[i]] + " " + std::to_string(scores[i]));
		}
	}

	return toReturn;
}*/

/*Crypto++
std::string DataBase::makeHash(const std::string & s)
{
	CryptoPP::MD5 hash;
	byte digest[CryptoPP::MD5::DIGESTSIZE];
	hash.CalculateDigest(digest, (byte*)s.c_str(), s.length());
	CryptoPP::HexEncoder encoder;
	std::string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();
	return output;
}*/

int DataBase::callback(void * notUsed, int argc, char ** argv, char ** colName)
{
	std::map<std::string, std::string> temp;

	for (int i = 1; i < argc; i++)
	{
		temp[colName[i]] = argv[i];
	}

	_results[std::atoi(argv[0])] = temp;

	return 0;
}

int DataBase::callbackPersonalStatus(void * notUsed, int argc, char ** argv, char ** colName)
{
	std::map<std::string, std::string> temp;

	for (int i = 1; i < argc; i++)
	{
		temp[colName[i]] = argv[i];
	}

	_personalResults[std::atoi(argv[0])].push_back(temp);
	return 0;
}

int DataBase::callbackBestScores(void * notUsed, int argc, char ** argv, char ** colName)
{
	std::map<std::string, std::string> temp;

	for (int i = 0; i < argc; i++)
	{
		temp[colName[i]] = argv[i];
	}

	_bestScoresResults[argv[1]].push_back(temp);
	return 0;
}
