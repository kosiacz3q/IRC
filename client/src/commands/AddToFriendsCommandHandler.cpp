#include "AddToFriendsCommandHandler.h"

#include "utils/utils.h"

using namespace rapidjson;


AddToFriendsCommandHandler::AddToFriendsCommandHandler(
		core::ClientDataPtr clientData,
		core::IDisplayerPtr displayer,
		core::IQueueHandlerPtr queueHandler,
		IRequestResponseManagerPtr responseManager)
			:_clientData(clientData),
			 _displayer(displayer),
			 _queueHandler(queueHandler),
			 _responseManager(responseManager)
{

}

AddToFriendsCommandHandler::~AddToFriendsCommandHandler()
{

}

void AddToFriendsCommandHandler::handle(std::string input)
{
	if (_clientData->Id < 1)
	{
		_displayer->displayLine("You must be connected first");
		return;
	}

	auto tokens = core::utils::tokenize(input, " \t");

	auto countOfParams = core::utils::getTokensCount(tokens);

	if (countOfParams != 1)
	{
		_displayer->displayLine("Invalid count of parameters, see #help");
		return;
	}

	_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

	rapidjson::Document document;
	document.SetObject();

	auto friendName = *tokens.begin();

	document.AddMember("user_id", Value().SetInt(_clientData->Id), document.GetAllocator());
	document.AddMember("request", "add_friend", document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());
	document.AddMember("username",  rapidjson::Value().SetString(friendName.c_str(), friendName.length()), document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void AddToFriendsCommandHandler::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status"}))
	{
		_displayer->displayLine("Some field are missing [list channel response]");
		return;
	}

	try
	{
		if (std::string("OK").compare(response["status"].GetString()) == 0)
		{
			_displayer->displayLine("Friend successfully added");
		}
		else
		{
			_displayer->displayLine("Error in message from server");
		}
	}
	catch(...)
	{
		_displayer->displayLine("Error occurred while handling response from server");
	}
}

std::string AddToFriendsCommandHandler::getCommand()
{
	return "#friend";
}

std::string AddToFriendsCommandHandler::getResponseCommand()
{
	return "#friend_response";
}

std::string AddToFriendsCommandHandler::getInfo()
{
	return "#friend <username> [Permanently adds user to our friend so you can will be notified when she/he arrive]";
}
