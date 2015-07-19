#include "LeaveChannelCommandHandler.h"

#include "utils/utils.h"

LeaveChannelCommandHandler::LeaveChannelCommandHandler(
		IRequestResponseManagerPtr responseManager,
		core::IDisplayerPtr displayer,
		core::IQueueHandlerPtr queueHandler,
		core::ClientDataPtr clientData)
		: _responseManager(responseManager),
		  _displayer(displayer),
		  _queueHandler(queueHandler),
		  _clientData(clientData)
{

}

LeaveChannelCommandHandler::~LeaveChannelCommandHandler()
{

}

void LeaveChannelCommandHandler::handle(std::string input)
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

	document.AddMember("request", "quit_channel", document.GetAllocator());
	document.AddMember("channel_name", rapidjson::Value().SetString(_clientData->Channel.c_str(), _clientData->Channel.length()), document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());
	document.AddMember("user_id",  rapidjson::Value().SetInt(_clientData->Id), document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void LeaveChannelCommandHandler::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status"}))
	{
		_displayer->displayLine("Some field are missing [leave channel response]");
		return;
	}

	if (std::string("OK").compare(response["status"].GetString()) == 0)
	{
		_displayer->displayLine(core::utils::format({"You successfully leave channel %1%" , _clientData->Channel } ));
		_clientData->Channel = "";
	}
	else
	{
		_displayer->displayLine("Error in message from server [leave channel]");
	}
}

std::string LeaveChannelCommandHandler::getCommand()
{
	return "#leave";
}

std::string LeaveChannelCommandHandler::getResponseCommand()
{
	return "#leave_response";
}

std::string LeaveChannelCommandHandler::getInfo()
{
	return "#leave [leaves actually joined channel]";
}
