#include "DisconnectCommandHandler.h"

#include <boost/algorithm/string.hpp>

#include "jsonParserFwd.h"


using namespace rapidjson;

DisconnectCommandHandler::DisconnectCommandHandler(
		core::ClientDataPtr clientData,
		core::IDisplayerPtr displayer,
		core::IQueueHandlerPtr queueHandler,
		IRequestResponseManagerPtr responseManager,
		IMessageListenerPtr messageListener,
		MessageListenerControllerPtr listenerController)
	:_clientData(clientData),
	 _displayer(displayer),
	 _queueHandler(queueHandler),
	 _responseManager(responseManager),
	 _messageListener(messageListener),
	 _listenerController(listenerController)
{

}

DisconnectCommandHandler::~DisconnectCommandHandler()
{

}

void DisconnectCommandHandler::handle(std::string input)
{
	boost::trim(input);

	if(!input.empty())
	{
		_displayer->displayLine("Invalid count of parameters, see #help");
		return;
	}

	if (_clientData->Id > 0)
	{
		_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

		std::string request = "quit_server";

		rapidjson::Document responseDoc;
		responseDoc.SetObject();
		responseDoc.AddMember("user_id", Value().SetInt(_clientData->Id), responseDoc.GetAllocator());
		responseDoc.AddMember("request", Value().SetString(request.c_str() , request.length()), responseDoc.GetAllocator());
		responseDoc.AddMember("request_id", Value().SetInt(_clientData->RequestId++), responseDoc.GetAllocator());

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		responseDoc.Accept(writer);

		_queueHandler->send(1, std::string(buffer.GetString()));
	}
	else
	{
		_displayer->displayLine("You are not connected");
	}
}

void DisconnectCommandHandler::handleResponse(rapidjson::Document& response)
{
	_listenerController->disableReading();
	//_queueHandler->send(_clientData->Id, ""); autopoke
	_clientData->Id = -1;
	_queueHandler->setQueueProvider(core::IQueueIdProviderPtr(nullptr));
	_displayer->displayLine("You are successfully disconnected");

}

std::string DisconnectCommandHandler::getCommand()
{
	return "#disconnect";
}

std::string DisconnectCommandHandler::getResponseCommand()
{
	return "#Disconnect_response";
}

std::string DisconnectCommandHandler::getInfo()
{
	return "#disconnect [disconnects from actually connected server]";
}
