#include "MessagesSender.h"

#include "jsonParserFwd.h"
#include "utils/utils.h"

using namespace rapidjson;

MessagesSender::MessagesSender(
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer,
		NotificationCounterPtr notificationCounter
		)
	:_queueHandler(queueHandler),
	 _displayer(displayer),
	 _notificationCounter(notificationCounter)
{

}

MessagesSender::~MessagesSender()
{

}

void MessagesSender::sendMessages(std::list<core::ClientDataPtr>&  targets, std::string message, core::ClientDataPtr sender)
{
	rapidjson::Document notificationToClient;

	for (auto iter = targets.begin(); iter != targets.end(); ++iter)
	{
		if (*iter != sender)
		{
			auto targetClient = (*iter);

			notificationToClient.SetObject();

			std::string notificationType = "new_message";
			notificationToClient.AddMember("notification", Value().SetString(notificationType.c_str(), notificationType.length()), notificationToClient.GetAllocator());

			auto nestedObject = Value(kObjectType);

			nestedObject.AddMember("source", Value().SetString(sender->Username.c_str(), sender->Username.length()) , notificationToClient.GetAllocator());
			nestedObject.AddMember("target", Value().SetString(targetClient->Username.c_str(), targetClient->Username.length()) , notificationToClient.GetAllocator());
			nestedObject.AddMember("text", Value().SetString(message.c_str(), message.length()) , notificationToClient.GetAllocator());
			nestedObject.AddMember("date", Value().SetInt(int(time(NULL))) , notificationToClient.GetAllocator());

			notificationToClient.AddMember("message", nestedObject, notificationToClient.GetAllocator());
			notificationToClient.AddMember("notification_id", Value().SetInt(_notificationCounter->requestNewNotificationId()), notificationToClient.GetAllocator());

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			notificationToClient.Accept(writer);

			_queueHandler->send( (*iter)->Id, std::string(buffer.GetString()));

			_displayer->displayLine(core::utils::format({"Message sent from %1% to %2% size %3%", sender->Username, targetClient->Username, std::to_string(message.length()) }));
		}
	}
}

