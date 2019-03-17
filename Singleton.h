#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class Singleton
{
public:
	~Singleton();
	static Singleton* getInstance();
	static std::mutex mutex;
	int getNum();
	void setNum(int num);

private:
	int num;
	static Singleton* instance;
	Singleton();
	
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};

