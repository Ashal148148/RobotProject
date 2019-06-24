#pragma once
#include <vector>
#include <iostream>
#include <string>
class Schedule
{
public:
	Schedule();
	~Schedule();
	std::vector<std::string>* getSchedule();
	void addAction(std::string command);
	int getScheduleSize();
	void flushSchedule();
	void setTimeStump(std::string timeStump);
	std::string getTimeStup();


private:
	std::vector<std::string>* _schedule;
	int _scheduleSize;
	std::string _nextActionTimeStump;
};

