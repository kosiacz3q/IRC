#ifndef REQUESTS_NOTIFICATIONCOUNTER_H_
#define REQUESTS_NOTIFICATIONCOUNTER_H_

#include <memory>

class NotificationCounter
{
	public:
		NotificationCounter();
		virtual ~NotificationCounter();

		int requestNewNotificationId()
		{
			return _notificationCounter++;
		}

	private:
		int _notificationCounter;
};

typedef std::shared_ptr<NotificationCounter> NotificationCounterPtr;

#endif /* REQUESTS_NOTIFICATIONCOUNTER_H_ */
