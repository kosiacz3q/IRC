#ifndef REQUESTS_LEAVECHANNELREQUESTHANDLER_H_
#define REQUESTS_LEAVECHANNELREQUESTHANDLER_H_

#include "IRequestHandler.h"

#include "IClientManager.h"
#include "../ChannelManager.h"

#include "coreFwd.h"

class LeaveChannelRequestHandler: public IRequestHandler
{
	public:
		LeaveChannelRequestHandler(
				ChannelManagerPtr channelManager,
				IClientManagerPtr clientsManager,
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer);
		virtual ~LeaveChannelRequestHandler();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:

		ChannelManagerPtr _channelManager;
		IClientManagerPtr _clientsManager;
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
};

#endif /* REQUESTS_LEAVECHANNELREQUESTHANDLER_H_ */
