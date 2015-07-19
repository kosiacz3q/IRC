#ifndef COMMANDS_JOINCHANNELCOMMAND_H_
#define COMMANDS_JOINCHANNELCOMMAND_H_

#include "coreFwd.h"

#include "ICommandHandler.h"

#include "IRequestResponseManager.h"

class JoinChannelCommand: public ICommandHandler
{
	public:
		JoinChannelCommand(
				IRequestResponseManagerPtr responseManager,
				core::IDisplayerPtr displayer,
				core::IQueueHandlerPtr queueHandler,
				core::ClientDataPtr clientData);

		virtual ~JoinChannelCommand();

		void handle(std::string input);

		void handleResponse(rapidjson::Document& response);

		std::string getCommand();

		std::string getResponseCommand();

		std::string getInfo();

	private:

		IRequestResponseManagerPtr _responseManager;
		core::IDisplayerPtr _displayer;
		core::IQueueHandlerPtr _queueHandler;
		core::ClientDataPtr _clientData;
};

#endif /* COMMANDS_JOINCHANNELCOMMAND_H_ */
