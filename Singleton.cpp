#include "Singleton.h"






Singleton::Singleton()
{
	this->num = 0;
}

Singleton::~Singleton()
{
	delete(instance);
}

Singleton* Singleton::getInstance()
{
	std::cout << "woof! " << std::endl;
	if (instance == nullptr)
	{
		mutex.lock();
		if (instance == nullptr)
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "moew! " << std::endl;
			instance = new Singleton();
		}
		mutex.unlock();
	}
	return instance;
}

int Singleton::getNum()
{
	return num;
}

void Singleton::setNum(int num)
{
	this->num = num;
}
