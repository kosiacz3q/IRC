#ifndef REQUESTS_MESSAGESSENDER_H_
#define REQUESTS_MESSAGESSENDER_H_

#include <list>
#include <string>
#include <memory>

#include "coreFwd.h"

#include "NotificationCounter.h"

class MessagesSender
{
	public:
		MessagesSender(
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer,
				NotificationCounterPtr notificationCounter);
		virtual ~MessagesSender();

		void sendMessages(std::list<core::ClientDataPtr>&  targets, std::string message,core::ClientDataPtr sender);

	private:
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
		NotificationCounterPtr _notificationCounter;
};

typedef std::shared_ptr<MessagesSender> MessagesSenderPtr;

#endif /* REQUESTS_MESSAGESSENDER_H_ */
