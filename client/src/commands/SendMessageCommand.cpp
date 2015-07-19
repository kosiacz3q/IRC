#include "SendMessageCommand.h"

#include <boost/algorithm/string.hpp>
#include <algorithm>

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

SendMessageCommand::SendMessageCommand(
		core::IQueueHandlerPtr queueHandler,
		core::ClientDataPtr clientData,
		core::IDisplayerPtr displayer,
		IRequestResponseManagerPtr responseManager)
	:_queueHandler(queueHandler),
	 _clientData(clientData),
	 _displayer(displayer),
	 _responseManager(responseManager)
{

}

SendMessageCommand::~SendMessageCommand()
{

}

void SendMessageCommand::handle(std::string input)
{
	if (_clientData->Id < 0)
	{
		_displayer->displayLine("You must be connected to the server first!");
		return;
	}

	if (_clientData->Channel.empty())
	{
		_displayer->displayLine("You must join the channel first!");
		return;
	}

	boost::trim(input);

	//input = input.substr(input.find_first_of(" \t")+1);

	if (input.empty())
	{
		_displayer->displayLine("Cannot send empty message");
		return;
	}
	else if(input.length() > 1900)
 	{
		_displayer->displayLine("Message is to long (max 1900 chars)");
		return;
	}

	_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

	rapidjson::Document document;
	document.SetObject();

	document.AddMember("user_id", rapidjson::Value().SetInt(_clientData->Id), document.GetAllocator());
	document.AddMember("request", "send_channel_message", document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());
	document.AddMember("channel_name", rapidjson::Value().SetString(_clientData->Channel.c_str(), _clientData->Channel.length()), document.GetAllocator());

	auto nestedObject = Value(kObjectType);

	nestedObject.AddMember("text", Value().SetString( input.c_str(), input.size()) , document.GetAllocator());
	document.AddMember("message", nestedObject, document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void SendMessageCommand::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status"}))
	{
		_displayer->displayLine("Some field are missing [send message response]");
		return;
	}

	if (std::string("OK").compare(response["status"].GetString()) != 0)
	{
		_displayer->displayLine(core::utils::format({"Your message could not be delivered (error %1%)" , response["status"].GetString() } ));
	}
}


std::string SendMessageCommand::getCommand()
{
	return "#sendMessage";
}

std::string SendMessageCommand::getResponseCommand()
{
	return "#handleSendMessage";
}

std::string SendMessageCommand::getInfo()
{
	return "#sendMessage <message> [Sends <message> to actually joined channel (this is default command if not specified)]";
}
