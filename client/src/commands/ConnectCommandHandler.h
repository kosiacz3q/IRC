#ifndef COMMANDS_CONNECTCOMMANDHANDLER_H_
#define COMMANDS_CONNECTCOMMANDHANDLER_H_

#include "coreFwd.h"

#include "ICommandHandler.h"
#include "MessageListenerController.h"

#include "IRequestResponseManager.h"

class ConnectCommandHandler: public ICommandHandler
{
	public:
		ConnectCommandHandler(
				core::ClientDataPtr clientData,
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer,
				IRequestResponseManagerPtr responseManager,
				IMessageListenerPtr messageListener,
				MessageListenerControllerPtr listenerController);

		virtual ~ConnectCommandHandler();

		void handle(std::string input);

		void handleResponse(rapidjson::Document& response);

		std::string getCommand();
		std::string getResponseCommand();

		std::string getInfo();

	private:

		core::ClientDataPtr _clientData;
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
		IRequestResponseManagerPtr _responseManager;
		IMessageListenerPtr _messageListener;
		MessageListenerControllerPtr _listenerController;
};

#endif /* COMMANDS_CONNECTCOMMANDHANDLER_H_ */
