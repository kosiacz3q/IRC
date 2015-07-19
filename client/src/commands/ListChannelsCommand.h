#ifndef COMMANDS_LISTCHANNELSCOMMAND_H_
#define COMMANDS_LISTCHANNELSCOMMAND_H_

#include "ICommandHandler.h"
#include "coreFwd.h"

#include "IRequestResponseManager.h"

class ListChannelsCommand: public ICommandHandler
{
	public:
		ListChannelsCommand(
				core::ClientDataPtr clientData,
				core::IDisplayerPtr displayer,
				core::IQueueHandlerPtr queueHandler,
				IRequestResponseManagerPtr responseManager);
		virtual ~ListChannelsCommand();

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

#endif /* COMMANDS_LISTCHANNELSCOMMAND_H_ */
