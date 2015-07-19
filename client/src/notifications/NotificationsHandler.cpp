#include "NotificationsHandler.h"

#include "utils/utils.h"

NotificationsHandler::NotificationsHandler(
		core::IDisplayerPtr displayer)
	:_displayer(displayer)
{

}

NotificationsHandler::~NotificationsHandler()
{

}


void NotificationsHandler::handle(rapidjson::Document& notification)
{
	if(!core::utils::checkFields(notification, {"notification"}))
	{
		_displayer->displayLine("Some field are missing [notification 1]");
		return;
	}

	if  (std::string("new_message").compare(notification["notification"].GetString()) != 0)
	{
		_displayer->displayLine("Unhandled notification type");
		return;
	}

	if(!core::utils::checkFields(notification, {"message"}))
	{
		_displayer->displayLine("Some field are missing [notification 2]");
		return;
	}

	_displayer->displayLine(core::utils::format({
		"[%1%] %2%",(notification["message"])["source"].GetString(), (notification["message"])["text"].GetString(),
	} ));

}
