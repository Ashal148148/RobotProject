#include "Schedule.h"



Schedule::Schedule()
{
	_scheduleSize = 0;
	_schedule = new std::vector<std::string>();
	_nextActionTimeStump = "00:00";
}


Schedule::~Schedule()
{
	if (_schedule != nullptr)
	{
		delete(_schedule);
	}
}

std::vector<std::string>* Schedule::getSchedule()
{
	return _schedule;
}

void Schedule::addAction(std::string command)
{
	(*_schedule).push_back(command);
	_scheduleSize++;
}

int Schedule::getScheduleSize()
{
	return _scheduleSize;
}

void Schedule::flushSchedule()
{
	_scheduleSize = 0;
	delete(_schedule);
	_schedule = new std::vector<std::string>();
}

void Schedule::setTimeStump(std::string timeStump)
{
	_nextActionTimeStump = timeStump;
}

std::string Schedule::getTimeStup()
{
	return _nextActionTimeStump;
}
