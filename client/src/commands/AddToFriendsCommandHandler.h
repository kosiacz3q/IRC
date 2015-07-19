#ifndef COMMANDS_ADDTOFRIENDSCOMMANDHANDLER_H_
#define COMMANDS_ADDTOFRIENDSCOMMANDHANDLER_H_

#include "ICommandHandler.h"
#include "coreFwd.h"

#include "IRequestResponseManager.h"

class AddToFriendsCommandHandler: public ICommandHandler
{
	public:
		AddToFriendsCommandHandler(
				core::ClientDataPtr clientData,
				core::IDisplayerPtr displayer,
				core::IQueueHandlerPtr queueHandler,
				IRequestResponseManagerPtr responseManager);
		virtual ~AddToFriendsCommandHandler();

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
};

#endif /* COMMANDS_ADDTOFRIENDSCOMMANDHANDLER_H_ */
