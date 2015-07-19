#include "ClientsManager.h"

#include <algorithm>

#include <boost/foreach.hpp>

using namespace core;

ClientsManager::ClientsManager()
{
	_clients = std::vector<core::ClientDataPtr>();
}

ClientsManager::~ClientsManager()
{

}

core::ClientDataPtr ClientsManager::getClientById(long id)
{
	BOOST_FOREACH(ClientDataPtr d , _clients)
	{
		if (d->Id == id)
			return d;
	}

	return nullptr;
}

void ClientsManager::addClient(core::ClientDataPtr clientData)
{
	_clients.push_back(clientData);
}

bool ClientsManager::isNameValid(std::string name)
{
	BOOST_FOREACH(ClientDataPtr d , _clients)
	{
		if (d->Username.compare(name) == 0)
			return false;
	}

	return true;
}

void ClientsManager::removeClient(core::ClientDataPtr clientData)
{
	auto toRemove = std::find(_clients.begin(), _clients.end(), clientData);
	if(toRemove  != _clients.end())
		_clients.erase(toRemove);
}

core::ClientDataPtr ClientsManager::getClientByName(std::string name)
{
	BOOST_FOREACH(ClientDataPtr d , _clients)
	{
		if (d->Username.compare(name) == 0)
			return d;
	}

	return nullptr;
}
