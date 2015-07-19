#ifndef COMMANDS_UNKNOWNCOMMANDHANDLER_H_
#define COMMANDS_UNKNOWNCOMMANDHANDLER_H_

#include "coreFwd.h"

#include "ICommandHandler.h"

#include "ICommandRegisterer.h"

class UnknownCommandHandler: public ICommandHandler
{
	public:
		UnknownCommandHandler(
				core::IDisplayerPtr displayer,
				ICommandRegistererPtr commandRegisterer);
		virtual ~UnknownCommandHandler();

		void handle(std::string input);

		std::string getCommand();

		void handleResponse(rapidjson::Document& response);

		std::string getResponseCommand();

		std::string getInfo();

	private:

		core::IDisplayerPtr _displayer;
		ICommandRegistererPtr _commandRegisterer;
};

#endif /* COMMANDS_UNKNOWNCOMMANDHANDLER_H_ */
