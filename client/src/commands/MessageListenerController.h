#ifndef COMMANDS_IMESSAGELISTENER_H_
#define COMMANDS_IMESSAGELISTENER_H_

#include <memory>

class MessageListenerController
{
	public:
		MessageListenerController()
			:_readingEnabled(false)
		{

		}

		virtual ~MessageListenerController() {};

		void disableReading()
		{
			_readingEnabled = false;
		}

		void enableReading()
		{
			_readingEnabled = true;
		}

		bool isReadingEnable()
		{
			return _readingEnabled;
		}

	private:
		bool _readingEnabled;
};

class IMessageListener
{
	public:
		virtual ~IMessageListener() {};
		virtual void startReading() = 0;
};

typedef std::shared_ptr<IMessageListener> IMessageListenerPtr;
typedef std::shared_ptr<MessageListenerController> MessageListenerControllerPtr;

#endif /* COMMANDS_IMESSAGELISTENER_H_ */
