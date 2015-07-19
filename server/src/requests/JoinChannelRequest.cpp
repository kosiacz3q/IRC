#include "JoinChannelRequest.h"

#include "jsonParserFwd.h"

#include "utils/utils.h"

using namespace rapidjson;

JoinChannelRequest::JoinChannelRequest(
		ChannelManagerPtr channelManager,
		IClientManagerPtr clientsManager,
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer)
		:_channelManager(channelManager),
		 _clientsManager(clientsManager),
		 _queueHandler(queueHandler),
		 _displayer(displayer)
{

}

JoinChannelRequest::~JoinChannelRequest()
{
}

void JoinChannelRequest::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "request" , "user_id", "channel_name"}))
	{
		_displayer->displayLine("Some fields are missing");
		return;
	}

	core::ClientDataPtr cd = _clientsManager->getClientById(doc["user_id"].GetInt());

	std::string status = "";
	bool channelCreated = false;

	if (!cd->Channel.empty())
	{
		status = "USER_ALREADY_JOINED_CHANNEL";
	}
	else
	{
		status = "OK";
		auto channel = _channelManager->getChannelByName(doc["channel_name"].GetString());

		if (!channel)
		{
			channelCreated = true;
			_channelManager->addChannel(doc["channel_name"].GetString());
			channel = _channelManager->getChannelByName(doc["channel_name"].GetString());
			_displayer->displayLine(core::utils::format({"Channel named %1% created", doc["channel_name"].GetString()}));
		}

		channel->addClient(cd);
	}

	rapidjson::Document responseDoc;
	responseDoc.SetObject();
	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("channel_created", Value().SetBool(channelCreated), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id",  rapidjson::Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string JoinChannelRequest::getType()
{
	return "join_channel";
}
