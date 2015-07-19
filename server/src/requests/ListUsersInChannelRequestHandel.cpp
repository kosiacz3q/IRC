#include "ListUsersInChannelRequestHandel.h"

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

ListUsersInChannelRequestHandel::ListUsersInChannelRequestHandel(
	core::IDisplayerPtr displayer,
	ChannelManagerPtr channelManager,
	core::IQueueHandlerPtr queueHandler)
		:_displayer(displayer),
		_channelManager(channelManager),
		_queueHandler(queueHandler)
{

}

ListUsersInChannelRequestHandel::~ListUsersInChannelRequestHandel()
{

}
void ListUsersInChannelRequestHandel::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "user_id", "channel_name" }))
	{
		_displayer->displayLine("Some field are missing");
		return;
	}

	Value users(kArrayType);

	auto channel = _channelManager->getChannelByName(doc["channel_name"].GetString());

	int countOfUsers = 0;

	for (auto iter = channel->Clients.begin(); iter != channel->Clients.end(); ++iter)
	{
		++countOfUsers;
		users.PushBack(Value().SetString((*iter)->Username.c_str(), (*iter)->Username.length()), doc.GetAllocator());
	}

	_displayer->displayLine(core::utils::format({"listed %1% users" , std::to_string(countOfUsers)}));

	std::string status = "OK";

	rapidjson::Document responseDoc;
	responseDoc.SetObject();

	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("response",  users, doc.GetAllocator());
	responseDoc.AddMember("request_id", Value().SetInt(doc["request_id"].GetInt()), doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string ListUsersInChannelRequestHandel::getType()
{
	return "list_users";
}
