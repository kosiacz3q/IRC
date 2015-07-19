#ifndef COMMANDS_ICOMMANDHANDLER_H_
#define COMMANDS_ICOMMANDHANDLER_H_

#include <string>
#include <memory>

#include "jsonParserFwd.h"

class ICommandHandler
{
	public:
		virtual ~ICommandHandler() {};

		virtual void handle(std::string input) = 0;

		virtual void handleResponse(rapidjson::Document& response) = 0;

		virtual std::string getCommand() = 0;
		virtual std::string getResponseCommand() = 0;

		virtual std::string getInfo() = 0;
};

typedef std::shared_ptr<ICommandHandler> ICommandHandlerPtr;

#endif /* COMMANDS_ICOMMANDHANDLER_H_ */
