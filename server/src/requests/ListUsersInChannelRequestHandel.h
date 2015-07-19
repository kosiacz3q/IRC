#ifndef REQUESTS_LISTUSERSINCHANNELREQUESTHANDEL_H_
#define REQUESTS_LISTUSERSINCHANNELREQUESTHANDEL_H_

#include "IRequestHandler.h"

#include "coreFwd.h"

#include "../ChannelManager.h"

class ListUsersInChannelRequestHandel: public IRequestHandler
{
	public:
		ListUsersInChannelRequestHandel(
				core::IDisplayerPtr displayer,
				ChannelManagerPtr channelManager,
				core::IQueueHandlerPtr queueHandler);
		virtual ~ListUsersInChannelRequestHandel();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		core::IDisplayerPtr _displayer;
		ChannelManagerPtr _channelManager;
		core::IQueueHandlerPtr _queueHandler;
};

#endif /* REQUESTS_LISTUSERSINCHANNELREQUESTHANDEL_H_ */
