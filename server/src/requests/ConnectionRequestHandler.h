#ifndef CONNECTIONREQUESTHANDLER_H_
#define CONNECTIONREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "IClientManager.h"
#include "ClientIdProvider.h"
#include "FriendManager.h"

#include "coreFwd.h"

class ConnectionRequestHandler : public IRequestHandler
{
	public:
		ConnectionRequestHandler(
				core::IQueueHandlerPtr queueHandler,
				IClientManagerPtr manager,
				core::IDisplayerPtr displayer,
				ClientIdProviderPtr clientIdProvider,
				FriendManagerPtr friendsManager);
		virtual ~ConnectionRequestHandler();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		IClientManagerPtr _manager;
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
		ClientIdProviderPtr  _clientIdProvider;
		FriendManagerPtr _friendsManager;
};

#endif /* CONNECTIONREQUESTHANDLER_H_ */
