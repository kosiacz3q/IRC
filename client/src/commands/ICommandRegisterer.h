#ifndef COMMANDS_ICOMMANDREGISTERER_H_
#define COMMANDS_ICOMMANDREGISTERER_H_

#include <vector>
#include <string>
#include <memory>

#include "ICommandHandler.h"

class ICommandRegisterer
{
	public:
		virtual ~ICommandRegisterer() {};

		virtual void registerCommand(ICommandHandlerPtr handler ) = 0;
		virtual std::vector<std::string> getCommands() = 0;
};

typedef std::shared_ptr<ICommandRegisterer> ICommandRegistererPtr;

#endif /* COMMANDS_ICOMMANDREGISTERER_H_ */
