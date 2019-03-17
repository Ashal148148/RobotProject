#pragma once
class Component
{
public:
	Component();
	Component(int port);
	int getPort();
	~Component();
	static void connectToComponent(Component component);//TODO

private:
	int _port;
};

