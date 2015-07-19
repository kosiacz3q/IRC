#include "LeaveChannelRequestHandler.h"

#include "jsonParserFwd.h"

#include "utils/utils.h"

using namespace rapidjson;

LeaveChannelRequestHandler::LeaveChannelRequestHandler(
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

LeaveChannelRequestHandler::~LeaveChannelRequestHandler()
{

}

void LeaveChannelRequestHandler::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "request" , "user_id", "channel_name"}))
	{
		_displayer->displayLine("Some field are missing");
		return;
	}

	core::ClientDataPtr cd = _clientsManager->getClientById(doc["user_id"].GetInt());

	std::string status = "no_user_channel";

	auto channel = _channelManager->getChannelByName(doc["channel_name"].GetString());

	if (channel != nullptr)
	{
		_displayer->displayLine(core::utils::format( {"%1% leave channel %2%", cd->Username , cd->Channel }));
		channel->removeClient(cd);
		status = "OK";
	}
	else
	{
		_displayer->displayLine("User try to leave without joining");
	}

	rapidjson::Document responseDoc;
	responseDoc.SetObject();
	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id",  rapidjson::Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string LeaveChannelRequestHandler::getType()
{
	return "quit_channel";
}
