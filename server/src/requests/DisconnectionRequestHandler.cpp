#include "DisconnectionRequestHandler.h"

#include <string>

#include "utils/utils.h"

using namespace rapidjson;

DisconnectionRequestHandler::DisconnectionRequestHandler(
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer,
		ChannelManagerPtr channelManager,
		IClientManagerPtr clientManager,
		FriendManagerPtr friendsManager)
	:_queueHandler(queueHandler),
	 _displayer(displayer),
	 _channelManager(channelManager),
	 _clientManager(clientManager),
	 _friendsManager(friendsManager)
{

}

DisconnectionRequestHandler::~DisconnectionRequestHandler()
{

}

void DisconnectionRequestHandler::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "user_id" }))
	{
			_displayer->displayLine("Some field are missing");
			return;
	}

	std::string status = "OK";

	auto client = _clientManager->getClientById(doc["user_id"].GetInt());

	if (client != nullptr)
	{
		auto channel = _channelManager->getChannelByName(client->Channel);

		if(channel != nullptr)
		{
			_displayer->displayLine(core::utils::format({"%1% removed from channel %2% due to disconnecting", client->Username, client->Channel}));
			channel->removeClient(client);
		}

		_friendsManager->removeNotifier(client);
	}

	rapidjson::Document responseDoc;
	responseDoc.SetObject();
	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id",  rapidjson::Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));

	_clientManager->removeClient(client);
}

std::string DisconnectionRequestHandler::getType()
{
	return "quit_server";
}

