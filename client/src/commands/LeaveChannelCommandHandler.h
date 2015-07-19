#ifndef COMMANDS_LEAVECHANNELCOMMANDHANDLER_H_
#define COMMANDS_LEAVECHANNELCOMMANDHANDLER_H_

#include "coreFwd.h"

#include "ICommandHandler.h"

#include "IRequestResponseManager.h"

class LeaveChannelCommandHandler : public ICommandHandler
{
	public:
		LeaveChannelCommandHandler(
				IRequestResponseManagerPtr responseManager,
				core::IDisplayerPtr displayer,
				core::IQueueHandlerPtr queueHandler,
				core::ClientDataPtr clientData);
		virtual ~LeaveChannelCommandHandler();

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

#endif /* COMMANDS_LEAVECHANNELCOMMANDHANDLER_H_ */
