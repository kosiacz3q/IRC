#ifndef REQUESTS_JOINCHANNELREQUEST_H_
#define REQUESTS_JOINCHANNELREQUEST_H_

#include "IRequestHandler.h"

#include "IClientManager.h"
#include "../ChannelManager.h"

#include "coreFwd.h"

class JoinChannelRequest: public IRequestHandler
{
	public:
		JoinChannelRequest(
				ChannelManagerPtr channelManager,
				IClientManagerPtr clientsManager,
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer);
		virtual ~JoinChannelRequest();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:

		ChannelManagerPtr _channelManager;
		IClientManagerPtr _clientsManager;
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
};

#endif /* REQUESTS_JOINCHANNELREQUEST_H_ */
