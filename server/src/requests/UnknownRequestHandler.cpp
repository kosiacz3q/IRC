#include "UnknownRequestHandler.h"

#include "jsonParserFwd.h"

#include "utils/utils.h"

using namespace rapidjson;
using namespace std;

UnknownRequestHandler::UnknownRequestHandler(core::IQueueHandlerPtr queueHandler,core::IDisplayerPtr displayer)
	:_queueHandler(queueHandler), _displayer(displayer)
{

}

UnknownRequestHandler::~UnknownRequestHandler()
{

}

void UnknownRequestHandler::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "user_id" }))
	{
		_displayer->displayLine("Some field are missing");
		return;
	}

	_displayer->displayLine("Unknown request");

	std::string status = "UNKNOWN_REQUEST";

	rapidjson::Document responseDoc;
	responseDoc.SetObject();
	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id", Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	Value availableRequests(kArrayType);

	availableRequests.PushBack("connect" , responseDoc.GetAllocator());
	availableRequests.PushBack("quit_server" , responseDoc.GetAllocator());
	availableRequests.PushBack("list_channels" , responseDoc.GetAllocator());
	availableRequests.PushBack("join_channel" , responseDoc.GetAllocator());
	availableRequests.PushBack("list_users" , responseDoc.GetAllocator());
	availableRequests.PushBack("quit_channel" , responseDoc.GetAllocator());
	availableRequests.PushBack("send_channel_message" , responseDoc.GetAllocator());
	availableRequests.PushBack("send_message" , responseDoc.GetAllocator());
	availableRequests.PushBack("add_to_friends" , responseDoc.GetAllocator());

	responseDoc.AddMember("available_requests", availableRequests, responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string UnknownRequestHandler::getType()
{
	return "UNKNOWN_REQUEST";
}
