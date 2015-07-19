#include "FriendManager.h"

#include "utils/utils.h"

#include <algorithm>

FriendManager::FriendManager(
		MessagesSenderPtr messageSender)
	:_friendsListener(std::map<std::string, std::list<core::ClientDataPtr>> ()),
	 _messageSender(messageSender)
{

}

FriendManager::~FriendManager()
{

}

void FriendManager::addFriendListener(std::string name, core::ClientDataPtr cd)
{
	auto toNotifyList = _friendsListener.find(name);

	if (toNotifyList != _friendsListener.end())
	{
		toNotifyList->second.push_back(cd);
	}
	else
	{
		_friendsListener.insert(std::pair<std::string, std::list<core::ClientDataPtr>>(name, {cd}));
	}

}

void FriendManager::userArrived(std::string name)
{
	auto toNotifyList = _friendsListener.find(name);

	if (toNotifyList != _friendsListener.end())
	{
		_messageSender->sendMessages(
				toNotifyList->second,
				core::utils::format({"Your friend %1% is now active", name}),
				core::ClientDataPtr(new core::ClientData("server" , -1))
		);
	}
}


void FriendManager::removeNotifier(core::ClientDataPtr tr)
{
	for (auto iter = _friendsListener.begin(); iter != _friendsListener.end(); ++iter)
	{
		auto toRemove= std::find(iter->second.begin(),iter->second.end(),tr);

		while (toRemove != iter->second.end())
		{
			iter->second.erase(toRemove);
			toRemove= std::find(iter->second.begin(),iter->second.end(),tr);
		}
	}
}
