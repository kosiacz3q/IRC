#include "SendPrivateMessageRequestHandler.h"

#include "utils/utils.h"

#include "jsonParserFwd.h"

using namespace rapidjson;

SendPrivateMessageRequestHandler::SendPrivateMessageRequestHandler(
		core::IDisplayerPtr displayer,
		core::IQueueHandlerPtr queueHandler,
		IClientManagerPtr clientManager,
		MessagesSenderPtr messageSender)
			:_displayer(displayer),
			_queueHandler(queueHandler),
			_clientManager(clientManager),
			_messageSender(messageSender)
{


}

SendPrivateMessageRequestHandler::~SendPrivateMessageRequestHandler()
{

}


void SendPrivateMessageRequestHandler::handleRequest(rapidjson::Document& doc)
{
	std::string status = "EMPTY";
	rapidjson::Document responseDoc;
	responseDoc.SetObject();

	if (!core::utils::checkFields(doc , {"request_id" , "user_id", "user", "message" }))
	{
		status = "INVALID_FIELDS";
		_displayer->displayLine("Some field are missing (private message)");
	}
	else
	{
		auto sender = _clientManager->getClientById(doc["user_id"].GetInt());
		auto target = _clientManager->getClientByName(doc["user"].GetString());

		if (target)
		{
			std::list<core::ClientDataPtr> t = {target};
			_messageSender->sendMessages( t  ,(doc["message"])["text"].GetString() , sender );

			status = "OK";
		}
		else
		{
			status = "THERE_IS_NO_USER";
		}
	}

	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id", Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);
	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string SendPrivateMessageRequestHandler::getType()
{
	return "send_message";
}

