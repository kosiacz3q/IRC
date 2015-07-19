#include "SendPrivateMessage.h"

#include <boost/algorithm/string.hpp>
#include <algorithm>

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

SendPrivateMessage::SendPrivateMessage(
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

SendPrivateMessage::~SendPrivateMessage()
{
	// TODO Auto-generated destructor stub
}

void SendPrivateMessage::handle(std::string input)
{
	if (_clientData->Id < 0)
	{
		_displayer->displayLine("You must be connected to the server first!");
		return;
	}

	auto tokens = core::utils::tokenize(input , " \t");

	auto tokensCount = core::utils::getTokensCount(tokens);

	if (tokensCount == 1 ) //user (...rest of the message...)
	{
		_displayer->displayLine("Cannot send empty message");
		return;
	}
	else if (tokensCount == 0)
	{
		_displayer->displayLine("Invalid count of parameters, see #help");
		return;
	}

	_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

	boost::trim(input);
	input += " ";
	auto feed = input.substr((input).find_first_of(" \t")+1);

	if(feed.length() > 1900)
	{
		_displayer->displayLine("Message is to long (max 1900 chars)");
		return;
	}

	rapidjson::Document document;
	document.SetObject();

	document.AddMember("user_id", rapidjson::Value().SetInt(_clientData->Id), document.GetAllocator());
	document.AddMember("request", "send_message", document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());
	document.AddMember("user", rapidjson::Value().SetString(tokens.begin()->c_str(),tokens.begin()->length()), document.GetAllocator());

	auto nestedObject = Value(kObjectType);
	nestedObject.AddMember("text", Value().SetString( feed.c_str(), feed.size()) , document.GetAllocator());
	document.AddMember("message", nestedObject, document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void SendPrivateMessage::handleResponse(rapidjson::Document& response)
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


std::string SendPrivateMessage::getCommand()
{
	return "#priv";
}

std::string SendPrivateMessage::getResponseCommand()
{
	return "#handlePriv";
}

std::string SendPrivateMessage::getInfo()
{
	return "#priv <user> <message> [Sends <message> to selected <user>]";
}
