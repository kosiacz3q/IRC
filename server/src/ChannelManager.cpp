#include "ChannelManager.h"

ChannelManager::ChannelManager()
{

}

ChannelManager::~ChannelManager()
{

}

void ChannelManager::addChannel(std::string name)
{
	_channelsMap.insert(std::pair<std::string, ChannelPtr>(name, ChannelPtr(new Channel(name))));
}

ChannelPtr ChannelManager::getChannelByName(std::string name)
{
	if (_channelsMap.find(name) != _channelsMap.end())
	{
		return _channelsMap.find(name)->second;
	}
	else
		return nullptr;
}

void ChannelManager::removeChannelByName(std::string name)
{
	if (_channelsMap.find(name) != _channelsMap.end())
	{
		_channelsMap.erase(_channelsMap.find(name));
	}
}


std::vector<std::string> ChannelManager::getChannelsNames()
{
	std::vector<std::string> result;
	for (auto iter = _channelsMap.begin(); iter != _channelsMap.end(); ++iter)
		result.push_back(iter->second->Name);

	return result;
}


