#ifndef REQUESTS_FRIENDMANAGER_H_
#define REQUESTS_FRIENDMANAGER_H_

#include  <map>
#include <list>
#include <memory>

#include "coreFwd.h"

#include "MessagesSender.h"

class FriendManager
{
	public:
		FriendManager(MessagesSenderPtr messageSender);
		virtual ~FriendManager();

		void addFriendListener(std::string name, core::ClientDataPtr);

		void userArrived(std::string name);

		void removeNotifier(core::ClientDataPtr);

	private:

		std::map<std::string, std::list<core::ClientDataPtr>> _friendsListener;
		MessagesSenderPtr _messageSender;
};

typedef std::shared_ptr<FriendManager> FriendManagerPtr;

#endif /* REQUESTS_FRIENDMANAGER_H_ */
