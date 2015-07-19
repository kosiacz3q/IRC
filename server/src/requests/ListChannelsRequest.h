#ifndef REQUESTS_LISTCHANNELSREQUEST_H_
#define REQUESTS_LISTCHANNELSREQUEST_H_

#include "IRequestHandler.h"

#include "coreFwd.h"

#include "../ChannelManager.h"

class ListChannelsRequest: public IRequestHandler
{
	public:
		ListChannelsRequest(
				core::IDisplayerPtr displayer,
				ChannelManagerPtr channelManager,
				core::IQueueHandlerPtr queueHandler);
		virtual ~ListChannelsRequest();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		core::IDisplayerPtr _displayer;
		ChannelManagerPtr _channelManager;
		core::IQueueHandlerPtr _queueHandler;
};

#endif /* REQUESTS_LISTCHANNELSREQUEST_H_ */
