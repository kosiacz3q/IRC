#ifndef COMMANDS_SENDPRIVATEMESSAGE_H_
#define COMMANDS_SENDPRIVATEMESSAGE_H_

#include "coreFwd.h"

#include "ICommandHandler.h"
#include "IRequestResponseManager.h"

class SendPrivateMessage: public ICommandHandler
{
	public:
		SendPrivateMessage(
				core::IQueueHandlerPtr queueHandler,
				core::ClientDataPtr clientData,
				core::IDisplayerPtr displayer,
				IRequestResponseManagerPtr responseManager);
		virtual ~SendPrivateMessage();

		void handle(std::string input);

		void handleResponse(rapidjson::Document& response);

		std::string getCommand();

		std::string getResponseCommand();

		std::string getInfo();

	private:

		core::IQueueHandlerPtr _queueHandler;
		core::ClientDataPtr _clientData;
		core::IDisplayerPtr _displayer;
		IRequestResponseManagerPtr _responseManager;
};

#endif /* COMMANDS_SENDPRIVATEMESSAGE_H_ */
