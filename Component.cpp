#include "Component.h"



Component::Component() : Component(-1) {}

Component::Component(int port)
{
	this->_port = port;
}

int Component::getPort()
{
	return this->_port;
}


Component::~Component()
{
}

void Component::connectToComponent(Component component)
{
}
