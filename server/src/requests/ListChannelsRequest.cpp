#include "ListChannelsRequest.h"

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

ListChannelsRequest::ListChannelsRequest(
		core::IDisplayerPtr displayer,
		ChannelManagerPtr channelManager,
		core::IQueueHandlerPtr queueHandler)
	:_displayer(displayer),
	 _channelManager(channelManager),
	 _queueHandler(queueHandler)
{

}

ListChannelsRequest::~ListChannelsRequest()
{

}

void ListChannelsRequest::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "user_id" }))
	{
		_displayer->displayLine("Some field are missing");
		return;
	}

	Value availableRequests(kArrayType);

	auto channels = _channelManager->getChannelsNames();

	for (auto iter = channels.begin(); iter != channels.end(); ++iter)
		availableRequests.PushBack(Value().SetString(iter->c_str(), iter->length()), doc.GetAllocator());

	_displayer->displayLine(core::utils::format({"listed %1% channels" , std::to_string(channels.size())}));

	std::string status = "OK";

	rapidjson::Document responseDoc;
	responseDoc.SetObject();

	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("response",  availableRequests, doc.GetAllocator());
	responseDoc.AddMember("request_id", Value().SetInt(doc["request_id"].GetInt()), doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string ListChannelsRequest::getType()
{
	return "list_channels";
}
