#ifndef COMMANDS_LISTUSERSCOMMANDHANDLER_H_
#define COMMANDS_LISTUSERSCOMMANDHANDLER_H_

#include "coreFwd.h"

#include "ICommandHandler.h"

#include "IRequestResponseManager.h"

class ListUsersCommandHandler: public ICommandHandler
{
	public:
		ListUsersCommandHandler(
				core::ClientDataPtr clientData,
				core::IDisplayerPtr displayer,
				core::IQueueHandlerPtr queueHandler,
				IRequestResponseManagerPtr responseManager);
		virtual ~ListUsersCommandHandler();

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

#endif /* COMMANDS_LISTUSERSCOMMANDHANDLER_H_ */
