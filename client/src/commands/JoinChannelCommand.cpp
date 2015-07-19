#include "JoinChannelCommand.h"

#include "utils/utils.h"

JoinChannelCommand::JoinChannelCommand(
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

JoinChannelCommand::~JoinChannelCommand()
{

}

void JoinChannelCommand::handle(std::string input)
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

	document.AddMember("request", "join_channel", document.GetAllocator());

	_clientData->Channel = *tokens.begin();

	document.AddMember("channel_name", rapidjson::Value().SetString(tokens.begin()->c_str(), tokens.begin()->length()), document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());
	document.AddMember("user_id",  rapidjson::Value().SetInt(_clientData->Id), document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void JoinChannelCommand::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status", "channel_created"}))
	{
		_displayer->displayLine("Some field are missing [join channel response]");
		return;
	}

	if (std::string("OK").compare(response["status"].GetString()) == 0)
	{
		_displayer->displayLine(core::utils::format(
					{"You successfully join channel %1% %2%",
					_clientData->Channel,
					response["channel_created"].GetBool() ? "(You create that channel)" : "" }));
	}
	else
	{
		_clientData->Channel = "";
		_displayer->displayLine("Error in message from server [join channel]");
	}
}

std::string JoinChannelCommand::getCommand()
{
	return "#join";
}

std::string JoinChannelCommand::getResponseCommand()
{
	return "#join_response";
}

std::string JoinChannelCommand::getInfo()
{
	return "#join <channelName> [joins <channelName> (if not exists, create channel with provided <channelName>)]";
}
