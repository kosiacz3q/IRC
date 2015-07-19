#include "ClientProtocolExecutor.h"

#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "jsonParserFwd.h"

#include "coreFwd.h"



ClientProtocolExecutor::ClientProtocolExecutor(
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer,
		IRequestResponseManagerPtr requestResponseManager,
		core::ClientDataPtr clientData,
		MessageListenerControllerPtr messageController,
		NotificationsHandlerPtr notificationsHandler)
		: _queueHandler(queueHandler),
		  _displayer(displayer),
		  _running(false),
		  _reading(false),
		  _pendingCommands(core::AtomicContainer<std::string>(getpid() % 9999)),
		  _requestCounter(0),
		  _requestResponseManager(requestResponseManager),
		  _clientData(clientData),
		  _messageController(messageController),
		  _notificationsHandler(notificationsHandler)
{

}

ClientProtocolExecutor::~ClientProtocolExecutor()
{

}

void ClientProtocolExecutor::addCommand(std::string command)
{
	_pendingCommands.pushBack(command);
}

void ClientProtocolExecutor::execute()
{
	_running = true;

	while (_running)
	{
		if (!_pendingCommands.empty())
		{
			handleCommand(_pendingCommands.popFirst());
		}
	}

	if(_readerThreadPtr)
		_readerThreadPtr->join();
}

void ClientProtocolExecutor::readRoutine()
{
	while (_messageController->isReadingEnable())
	{
		auto income = std::string(_queueHandler->getMessage(_clientData->Id).c_str());

		if(!income.empty() && _messageController->isReadingEnable())
		{
			rapidjson::Document incomingRequest;
			incomingRequest.Parse(income.c_str());

			if(incomingRequest.HasMember("request_id") && incomingRequest.HasMember("status"))
			{
				auto responseHandler = _commandToHandler.find(_requestResponseManager->getHandler(incomingRequest["request_id"].GetInt()));

				if (std::string("UNKNOWN_REQUEST").compare(incomingRequest["status"].GetString()) == 0)
				{
					_displayer->displayLine("Unknown request");
				}
				else if (responseHandler != _commandToHandler.end())
				{
					responseHandler->second->handleResponse(incomingRequest);
				}
				else
				{
					_displayer->displayLine("Unknown request id");
				}
			}
			else if(incomingRequest.HasMember("notification_id"))
			{
				_notificationsHandler->handle(incomingRequest);
			}
			else
			{
				_displayer->displayLine("Corrupted server response");
			}
		}
	}
}

void ClientProtocolExecutor::handleCommand(std::string command)
{
	if (!command.empty() && command[0] == '#')
	{
		boost::char_separator<char> sep(" ");
		boost::tokenizer<boost::char_separator<char>> tokens(command, sep);

		if (tokens.begin()->compare("#exit") == 0)
		{
			handleCommand("#disconnect");
			_running = false;
		}
		else
		{
			if (_commandToHandler.find(*tokens.begin()) != _commandToHandler.end())
			{
				boost::trim(command);

				auto ddd = *tokens.begin();
				auto handler = _commandToHandler.find(*tokens.begin())->second;
				command += " ";
				auto feed = command.substr((command).find_first_of(" \t")+1);
				handler->handle(feed);
			}
			else
			{
				handleCommand("#help " + *tokens.begin());
			}
		}
	}
	else if (!command.empty())
	{
		handleCommand("#sendMessage " + command);
	}
}

void ClientProtocolExecutor::registerCommand(ICommandHandlerPtr handler )
{
	_commandToHandler.insert(std::pair<std::string, ICommandHandlerPtr>(handler->getCommand(), handler));
	_commandToHandler.insert(std::pair<std::string, ICommandHandlerPtr>(handler->getResponseCommand(), handler));
}

std::vector<std::string> ClientProtocolExecutor::getCommands()
{
	auto result = std::vector<std::string>();

	for (auto commanditer = _commandToHandler.begin(); commanditer != _commandToHandler.end(); ++commanditer )
	{
		if (commanditer->first.find("response") >= commanditer->first.size())
			result.push_back(commanditer->second->getInfo());
	}

	result.push_back("#exit [exit]");

	return result;
}

void ClientProtocolExecutor::startReading()
{
	_readerThreadPtr = std::shared_ptr<std::thread>(new std::thread(&ClientProtocolExecutor::readRoutine, *this));
}

