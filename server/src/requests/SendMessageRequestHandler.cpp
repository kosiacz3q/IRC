#include "SendMessageRequestHandler.h"

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

SendMessageRequestHandler::SendMessageRequestHandler(
		core::IDisplayerPtr displayer,
		ChannelManagerPtr channelManager,
		core::IQueueHandlerPtr queueHandler,
		IClientManagerPtr clientManager,
		MessagesSenderPtr messageSender)
			:_displayer(displayer),
			_channelManager(channelManager),
			_queueHandler(queueHandler),
			_clientManager(clientManager),
			_messageSender(messageSender)
{

}

SendMessageRequestHandler::~SendMessageRequestHandler()
{

}

void SendMessageRequestHandler::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "user_id", "channel_name", "message" }))
	{
		_displayer->displayLine("Some fields are missing");
		return;
	}

	std::string status = "";

	auto sender = _clientManager->getClientById(doc["user_id"].GetInt());

	ChannelPtr channel = _channelManager->getChannelByName(doc["channel_name"].GetString());

	auto channelName = doc["channel_name"].GetString();
	auto clientsChannelName = sender->Channel;

	if(clientsChannelName.compare(channelName) != 0)
	{
		status = "WRONG CHANNEL";
		_displayer->displayLine(core::utils::format({
			"User %1% is not member of %2% (is member of %3%)",
			sender->Username,
			channelName,
			clientsChannelName
		}));
	}
	else if (channel != nullptr)
	{
		status = "OK";
		_messageSender->sendMessages( channel->Clients , (doc["message"])["text"].GetString(), sender );
	}
	else
	{
		_displayer->displayLine(core::utils::format({"User %1% not joined to any channel" , sender->Username}));
		status = "NOT_JOINED";
	}

	rapidjson::Document responseDoc;
	responseDoc.SetObject();

	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id", Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string SendMessageRequestHandler::getType()
{
	return "send_channel_message";
}
