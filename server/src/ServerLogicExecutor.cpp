#include "ServerLogicExecutor.h"

#include "utils/utils.h"

using namespace std;

ServerLogicExecutor::ServerLogicExecutor(
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer,
		IClientManagerPtr clientManager)
		: _queueHandler(queueHandler),
		  _displayer(displayer),
		  _requestTypeToHandler(std::map<std::string, IRequestHandlerPtr>()),
		  _running(false),
		  _clientManager(clientManager)
{

}

ServerLogicExecutor::~ServerLogicExecutor()
{

}

void ServerLogicExecutor::execute()
{
	_running = true;

	while (_running)
	{
		rapidjson::Document incomingRequest;
		incomingRequest.Parse(_queueHandler->getMessage(1).c_str());

		if (!_running)
			continue;

		if (incomingRequest.HasMember("notification_id"))
		{
			_displayer->displayLine("Notification confiramtion received");
			continue;
		}

		core::ClientDataPtr client = nullptr;
		//---------------------------LOGGING-----------------------------
		std::string clientName = "unregister";
		std::string userId = "not provided";

		if(incomingRequest.HasMember("user_id"))
		{
			userId = std::to_string(incomingRequest["user_id"].GetInt());

			client = _clientManager->getClientById(incomingRequest["user_id"].GetInt());
			if(client)
				clientName = client->Username;
		}

		auto requestId = std::to_string(incomingRequest["request_id"].GetInt());

		_displayer->displayLine(
				core::utils::format({"Request %1% (id:%2%) from client %3% (%4%)",
									 incomingRequest["request"].GetString(),
									 requestId,
									 clientName,
									 userId

		}));
		//---------------------------LOGGING-----------------------------

		if (client == nullptr && std::string("connect").compare(incomingRequest["request"].GetString()) != 0)
		{
			_displayer->displayLine("request will be not handled (unknown user");
			continue;
		}

		auto handler =  _requestTypeToHandler.find(incomingRequest["request"].GetString());

		if (handler == _requestTypeToHandler.end())
		{
			_requestTypeToHandler.find("UNKNOWN_REQUEST")->second->handleRequest(incomingRequest);
		}
		else
		{
			handler->second->handleRequest(incomingRequest);
		}
	}
}

void ServerLogicExecutor::registerHandler(IRequestHandlerPtr handler)
{
	_requestTypeToHandler.insert(std::pair<std::string, IRequestHandlerPtr> ( handler->getType() , handler) );
}

void ServerLogicExecutor::stop()
{
	_running = false;

	rapidjson::Document responseDoc;
	responseDoc.SetObject();

	responseDoc.AddMember("request", rapidjson::Value().SetString(_exitString.c_str(), _exitString.length()), responseDoc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	responseDoc.Accept(writer);

	_queueHandler->send(1,  std::string(buffer.GetString()));
}
