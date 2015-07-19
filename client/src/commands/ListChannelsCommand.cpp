#include "ListChannelsCommand.h"

#include "utils/utils.h"

using namespace rapidjson;

ListChannelsCommand::ListChannelsCommand(
		core::ClientDataPtr clientData,
		core::IDisplayerPtr displayer,
		core::IQueueHandlerPtr queueHandler,
		IRequestResponseManagerPtr responseManager)
	:_clientData(clientData),
	 _displayer(displayer),
	 _queueHandler(queueHandler),
	 _responseManager(responseManager)
{


}

ListChannelsCommand::~ListChannelsCommand()
{

}


void ListChannelsCommand::handle(std::string input)
{
	if (_clientData->Id < 1)
	{
		_displayer->displayLine("You must be connected first");
		return;
	}

	boost::trim(input);

	if (!input.empty())
	{
		_displayer->displayLine("Invalid count of parameters, see #help");
		return;
	}

	_responseManager->registerResponseType(_clientData->RequestId ,getResponseCommand());

	rapidjson::Document document;
	document.SetObject();

	document.AddMember("user_id", Value().SetInt(_clientData->Id), document.GetAllocator());
	document.AddMember("request", "list_channels", document.GetAllocator());
	document.AddMember("request_id",  rapidjson::Value().SetInt(_clientData->RequestId++), document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	_queueHandler->send(1, std::string(buffer.GetString()));
}

void ListChannelsCommand::handleResponse(rapidjson::Document& response)
{
	if(!core::utils::checkFields(response, {"status", "response"}))
	{
		_displayer->displayLine("Some field are missing [list channel response]");
		return;
	}

	try
	{
		if (std::string("OK").compare(response["status"].GetString()) == 0)
		{
			const Value& a = response["response"];

			_displayer->displayLine("Available channels");
			for (SizeType i = 0; i < a.Size(); i++)
				_displayer->displayLine(core::utils::format({"%1%. %2%", std::to_string(i), a[i].GetString()}));
		}
		else
		{
			_displayer->displayLine("Error in message from server");
		}
	}
	catch(...)
	{
		_displayer->displayLine("Error occurred while handling response from server");
	}
}

std::string ListChannelsCommand::getCommand()
{
	return "#list_channels";
}

std::string ListChannelsCommand::getResponseCommand()
{
	return "#list_channels_response";
}

std::string ListChannelsCommand::getInfo()
{
	return "#list_channels [list channels that are actually created on server]";
}
