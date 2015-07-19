#include "ConnectCommandHandler.h"

#include "utils/utils.h"

ConnectCommandHandler::ConnectCommandHandler(
		core::ClientDataPtr clientData,
		core::IQueueHandlerPtr queueHandler,
		core::IDisplayerPtr displayer,
		IRequestResponseManagerPtr responseManager,
		IMessageListenerPtr messageListener,
		MessageListenerControllerPtr listenerController)
		: _clientData(clientData),
		  _queueHandler(queueHandler),
		  _displayer(displayer),
		  _responseManager(responseManager),
		  _messageListener(messageListener),
		  _listenerController(listenerController)
{

}

ConnectCommandHandler::~ConnectCommandHandler()
{

}

void ConnectCommandHandler::handle(std::string input)
{

	auto tokens = core::utils::tokenize(input, " \t");

	auto countOfParams = core::utils::getTokensCount(tokens);

	if (countOfParams != 1)
	{
		_displayer->displayLine("Invalid count of parameters, see #help");
		return;
	}

	_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

	std::string dsd = *tokens.begin();

	_queueHandler->setQueueProvider(core::IQueueIdProviderPtr(new core::QueueHolder(std::stoi(*tokens.begin()))));

	_clientData->Id = getpid();

	_listenerController->enableReading();
	_messageListener->startReading();

	rapidjson::Document document;
	document.SetObject();

	document.AddMember("request", "connect", document.GetAllocator());

	document.AddMember("username", rapidjson::Value().SetString(_clientData->Username.c_str(), _clientData->Username.length()), document.GetAllocator());
	document.AddMember("temp_id",  rapidjson::Value().SetInt(_clientData->Id), document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void ConnectCommandHandler::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status", "user_id"}))
	{
		_displayer->displayLine("Some field are missing [connect response]");
		return;
	}

	if (std::string("OK").compare(response["status"].GetString()) == 0)
	{
		//if (response["user_id"].GetInt() != _clientData->Id)
		{
			//auto lastId = _clientData->Id;
			_clientData->Id =  response["user_id"].GetInt();
			//_queueHandler->send(lastId, std::string("")); autopoke
		}

		_displayer->displayLine("You successfully connect to server");
	}
	else if(std::string("NAME_CONFLICT").compare(response["status"].GetString()))
	{
		_listenerController->disableReading();
		_queueHandler->send(_clientData->Id, std::string(""));

		_clientData->Id =  -1;
		_queueHandler->setQueueProvider(core::IQueueIdProviderPtr(nullptr));
		_displayer->displayLine("Connection to server refused. Name is reserved already");
	}
	else
	{
		_listenerController->disableReading();
		_queueHandler->send(_clientData->Id, std::string(""));

		_clientData->Id =  -1;
		_queueHandler->setQueueProvider(core::IQueueIdProviderPtr(nullptr));
		_displayer->displayLine("Connection to server refused");
	}

}

std::string ConnectCommandHandler::getCommand()
{
	return "#connect";
}

std::string ConnectCommandHandler::getResponseCommand()
{
	return "#Connect_response";
}

std::string ConnectCommandHandler::getInfo()
{
	return "#connect <serverAddress> [tries to join server with <serverAddress>]";
}
