#ifndef REQUESTS_SENDPRIVATEMESSAGEREQUESTHANDLER_H_
#define REQUESTS_SENDPRIVATEMESSAGEREQUESTHANDLER_H_

#include "IRequestHandler.h"
#include "MessagesSender.h"

#include "coreFwd.h"

#include "../ChannelManager.h"
#include "../ClientsManager.h"

class SendPrivateMessageRequestHandler : public IRequestHandler
{
	public:
		SendPrivateMessageRequestHandler(
			core::IDisplayerPtr displayer,
			core::IQueueHandlerPtr queueHandler,
			IClientManagerPtr clientManager,
			MessagesSenderPtr messageSender);
		virtual ~SendPrivateMessageRequestHandler();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		core::IDisplayerPtr _displayer;
		core::IQueueHandlerPtr _queueHandler;
		IClientManagerPtr _clientManager;
		MessagesSenderPtr _messageSender;
};

#endif /* REQUESTS_SENDPRIVATEMESSAGEREQUESTHANDLER_H_ */
