#include "UnknownCommandHandler.h"

#include <boost/format.hpp>
#include <boost/foreach.hpp>

UnknownCommandHandler::UnknownCommandHandler(
		core::IDisplayerPtr displayer,
		ICommandRegistererPtr commandRegisterer)
	:_displayer(displayer),
	 _commandRegisterer(commandRegisterer)
{

}

UnknownCommandHandler::~UnknownCommandHandler()
{

}

void UnknownCommandHandler::handle(std::string input)
{
	auto commands = _commandRegisterer->getCommands();

	for (auto iter = commands.begin(); iter != commands.end(); ++iter)
		_displayer->displayLine(*iter);
}

void UnknownCommandHandler::handleResponse(rapidjson::Document& response)
{

}

std::string UnknownCommandHandler::getCommand()
{
	return "#help";
}


std::string UnknownCommandHandler::getResponseCommand()
{
	return "#responseHelp";
}

std::string UnknownCommandHandler::getInfo()
{
	return "#help [displays available commands]";
}
