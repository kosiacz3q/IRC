#ifndef NOTIFICATIONS_NEWMESSAGENOTIFICATIONHANDLER_H_
#define NOTIFICATIONS_NEWMESSAGENOTIFICATIONHANDLER_H_

#include <memory>

#include "coreFwd.h"
#include "jsonParserFwd.h"


class NotificationsHandler
{
	public:
		NotificationsHandler(
				core::IDisplayerPtr displayer);

		virtual ~NotificationsHandler();

		void handle(rapidjson::Document& notification);

	private:
		core::IDisplayerPtr _displayer;
};

typedef std::shared_ptr<NotificationsHandler> NotificationsHandlerPtr;

#endif /* NOTIFICATIONS_NEWMESSAGENOTIFICATIONHANDLER_H_ */
