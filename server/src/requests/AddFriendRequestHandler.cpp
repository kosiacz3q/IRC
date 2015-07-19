#include "AddFriendRequestHandler.h"

#include "jsonParserFwd.h"

#include "utils/utils.h"

using namespace rapidjson;

AddFriendRequestHandler::AddFriendRequestHandler(
		IClientManagerPtr clientsManager,
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer,
		FriendManagerPtr friendsManager)
		:_clientsManager(clientsManager),
		 _queueHandler(queueHandler),
		 _displayer(displayer),
		 _friendsManager(friendsManager)
{

}

AddFriendRequestHandler::~AddFriendRequestHandler()
{

}

void AddFriendRequestHandler::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"request_id" , "request" , "user_id", "username"}))
	{
		_displayer->displayLine("Some fields are missing");
		return;
	}

	core::ClientDataPtr cd = _clientsManager->getClientById(doc["user_id"].GetInt());

	_friendsManager->addFriendListener(doc["username"].GetString(), cd);

	std::string status = "OK";
	rapidjson::Document responseDoc;
	responseDoc.SetObject();
	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id",  rapidjson::Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["user_id"].GetInt(), std::string(buffer.GetString()));
}

std::string AddFriendRequestHandler::getType()
{
	return "add_friend";
}
