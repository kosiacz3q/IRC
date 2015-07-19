#include "ListUsersCommandHandler.h"

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

ListUsersCommandHandler::ListUsersCommandHandler(
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

ListUsersCommandHandler::~ListUsersCommandHandler()
{

}

void ListUsersCommandHandler::handle(std::string input)
{
	if (_clientData->Id < 1)
	{
		_displayer->displayLine("You must be connected first");
		return;
	}

	auto tokens = core::utils::tokenize(input, " \t");

	auto countOfParams = core::utils::getTokensCount(tokens);

	if (countOfParams != 0)
	{
		_displayer->displayLine("Invalid count of parameters, see #help");
		return;
	}

	_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

	rapidjson::Document document;
	document.SetObject();

	document.AddMember("request", "list_users", document.GetAllocator());

	document.AddMember("channel_name", rapidjson::Value().SetString(_clientData->Channel.c_str(), _clientData->Channel.length()), document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());
	document.AddMember("user_id",  rapidjson::Value().SetInt(_clientData->Id), document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void ListUsersCommandHandler::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status", "response"}))
	{
		_displayer->displayLine("Some field are missing [list user response]");
		return;
	}

	if (std::string("OK").compare(response["status"].GetString()) == 0)
	{
		const Value& a = response["response"];

		_displayer->displayLine(core::utils::format({"Users in channel %1%", _clientData->Channel}));
		for (SizeType i = 0; i < a.Size(); i++)
			_displayer->displayLine(core::utils::format({"%1%. %2%", std::to_string(i), a[i].GetString()}));
	}
	else
	{
		_displayer->displayLine("Error in message from server [join channel]");
	}
}

std::string ListUsersCommandHandler::getCommand()
{
	return "#list_users";
}

std::string ListUsersCommandHandler::getResponseCommand()
{
	return "#list_users_response";
}

std::string ListUsersCommandHandler::getInfo()
{
	return "#list_users [list users in actually joined channel]";
}
