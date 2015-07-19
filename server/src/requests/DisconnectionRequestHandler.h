#ifndef REQUESTS_DISCONNECTIONREQUESTHANDLER_H_
#define REQUESTS_DISCONNECTIONREQUESTHANDLER_H_

#include "IRequestHandler.h"

#include "coreFwd.h"

#include "../ChannelManager.h"
#include "IClientManager.h"

#include "FriendManager.h"

class DisconnectionRequestHandler : public IRequestHandler
{
	public:
		DisconnectionRequestHandler(
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer,
				ChannelManagerPtr channelManager,
				IClientManagerPtr clientManager,
				FriendManagerPtr friendsManager);

		virtual ~DisconnectionRequestHandler();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
		ChannelManagerPtr _channelManager;
		IClientManagerPtr _clientManager;
		FriendManagerPtr _friendsManager;
};

#endif /* REQUESTS_DISCONNECTIONREQUESTHANDLER_H_ */
