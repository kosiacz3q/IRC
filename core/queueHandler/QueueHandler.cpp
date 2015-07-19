#include "QueueHandler.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/errno.h>

#include <algorithm>

#include "QueueException.h"

const int MAX_MESSAGE_SIZE = 2047 - sizeof(long);

namespace core
{

struct rawMessage
{
		long type;
		char tab[MAX_MESSAGE_SIZE];
};

QueueHandler::QueueHandler(IQueueIdProviderPtr queueIdProvider)
		: _queueId(-1), _queueIdProvider(queueIdProvider)
{

}

QueueHandler::QueueHandler()
		: _queueId(-1), _queueIdProvider(nullptr)
{

}

QueueHandler::~QueueHandler()
{

}

void QueueHandler::setQueueProvider(IQueueIdProviderPtr queueIdProvider)
{
	_queueIdProvider = queueIdProvider;
}

std::string QueueHandler::getMessage(int type)
{
	rawMessage _rawMessage;

	if (msgrcv(_queueIdProvider->getId(), &_rawMessage, sizeof(rawMessage), type, 0) < 0)
		throw QueueException("Unable to read any message");

	return std::string(_rawMessage.tab);
}

void QueueHandler::send(long type, const std::string& message)
{
	if (message.length() > MAX_MESSAGE_SIZE)
		throw QueueException("Message size to long");

	rawMessage _rawMessage;

	_rawMessage.type = type;

	std::copy(message.begin(), message.end(), _rawMessage.tab);
	_rawMessage.tab[message.length()] = '\0';

	if (msgsnd(_queueIdProvider->getId(), &_rawMessage, sizeof(rawMessage::tab), 0) < 0)
		throw QueueException("Message could not be send");
}

} /* namespace core */

