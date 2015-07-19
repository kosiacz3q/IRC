#ifndef REQUESTS_ADDFRIENDREQUESTHANDLER_H_
#define REQUESTS_ADDFRIENDREQUESTHANDLER_H_

#include "IRequestHandler.h"


#include "IClientManager.h"
#include "../ChannelManager.h"

#include "coreFwd.h"
#include "FriendManager.h"

class AddFriendRequestHandler: public IRequestHandler
{
	public:
		AddFriendRequestHandler(
				IClientManagerPtr clientsManager,
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer,
				FriendManagerPtr friendsManager);
		virtual ~AddFriendRequestHandler();


		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:

		IClientManagerPtr _clientsManager;
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
		FriendManagerPtr _friendsManager;


};

#endif /* REQUESTS_ADDFRIENDREQUESTHANDLER_H_ */
