#include "ConnectionRequestHandler.h"

#include <string>
#include "boost/format.hpp"

#include "utils/utils.h"

using namespace std;
using namespace core;
using namespace rapidjson;
using namespace boost;

ConnectionRequestHandler::ConnectionRequestHandler(
		core::IQueueHandlerPtr queueHandler,
		IClientManagerPtr manager,
		core::IDisplayerPtr displayer,
		ClientIdProviderPtr  clientIdProvider,
		FriendManagerPtr friendsManager)
	: _manager(manager),
	  _queueHandler(queueHandler),
	  _displayer(displayer),
	  _clientIdProvider(clientIdProvider),
	  _friendsManager(friendsManager)
{

}

ConnectionRequestHandler::~ConnectionRequestHandler()
{

}

void ConnectionRequestHandler::handleRequest(rapidjson::Document& doc)
{
	if (!core::utils::checkFields(doc , {"username" , "temp_id" , "request_id"}))
	{
		_displayer->displayLine("Some fields are missing");
		return;
	}

	ClientDataPtr cd = core::ClientDataPtr(new ClientData());

	cd->Username = doc["username"].GetString();
	cd->Id = _clientIdProvider->getUniqeId();

	std::string status;

	if (_manager->isNameValid(cd->Username))
	{
		status = "OK";
		_displayer->displayLine((format("[User connected] name : %1%") % cd->Username).str());
		_manager->addClient(cd);

		_friendsManager->userArrived(cd->Username);
	}
	else
	{
		_displayer->displayLine((format("[Requested name duplicated] name : %1%") % cd->Username).str());
		status = "NAME_CONFLICT";
	}

	rapidjson::Document responseDoc;
	responseDoc.SetObject();
	responseDoc.AddMember("status", Value().SetString(status.c_str(), status.length()), responseDoc.GetAllocator());
	responseDoc.AddMember("user_id", Value().SetInt(cd->Id), responseDoc.GetAllocator());
	responseDoc.AddMember("request_id",  rapidjson::Value().SetInt(doc["request_id"].GetInt()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(doc["temp_id"].GetInt(), std::string(buffer.GetString()));
}

std::string ConnectionRequestHandler::getType()
{
	return "connect";
}

