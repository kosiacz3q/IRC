#ifndef COMMANDS_DISCONNECTCOMMANDHANDLER_H_
#define COMMANDS_DISCONNECTCOMMANDHANDLER_H_

#include "coreFwd.h"

#include "ICommandHandler.h"
#include "IRequestResponseManager.h"
#include "MessageListenerController.h"

class DisconnectCommandHandler: public ICommandHandler
{
	public:
		DisconnectCommandHandler(
				core::ClientDataPtr clientData,
				core::IDisplayerPtr displayer,
				core::IQueueHandlerPtr queueHandler,
				IRequestResponseManagerPtr responseManager,
				IMessageListenerPtr messageListener,
				MessageListenerControllerPtr listenerController
				);
		virtual ~DisconnectCommandHandler();

		void handle(std::string input);

		void handleResponse(rapidjson::Document& response);

		std::string getCommand();

		std::string getResponseCommand();

		std::string getInfo();

	private:
		core::ClientDataPtr _clientData;
		core::IDisplayerPtr _displayer;
		core::IQueueHandlerPtr _queueHandler;
		IRequestResponseManagerPtr _responseManager;
		IMessageListenerPtr _messageListener;
		MessageListenerControllerPtr _listenerController;
};

#endif /* COMMANDS_DISCONNECTCOMMANDHANDLER_H_ */
