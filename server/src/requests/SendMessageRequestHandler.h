#ifndef REQUESTS_SENDMESSAGEREQUESTHANDLER_H_
#define REQUESTS_SENDMESSAGEREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "MessagesSender.h"

#include "coreFwd.h"

#include "../ChannelManager.h"
#include "../ClientsManager.h"

class SendMessageRequestHandler: public IRequestHandler
{
	public:
		SendMessageRequestHandler(
				core::IDisplayerPtr displayer,
				ChannelManagerPtr channelManager,
				core::IQueueHandlerPtr queueHandler,
				IClientManagerPtr clientManager,
				MessagesSenderPtr messageSender);

		virtual ~SendMessageRequestHandler();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		core::IDisplayerPtr _displayer;
		ChannelManagerPtr _channelManager;
		core::IQueueHandlerPtr _queueHandler;
		IClientManagerPtr _clientManager;
		MessagesSenderPtr _messageSender;
};

#endif /* REQUESTS_SENDMESSAGEREQUESTHANDLER_H_ */
