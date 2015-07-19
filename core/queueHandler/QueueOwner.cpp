#include "QueueOwner.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

#include "QueueException.h"

namespace core
{

QueueOwner::~QueueOwner()
{
	if (msgctl(_queueId, IPC_RMID, nullptr) == 0)
		std::cout << "[Queue successfully removed]" << std::endl;
	else
		std::cout << "[Error occurred while removing queue]" << std::endl;
}

QueueOwner::QueueOwner(key_t key)
{
	_queueId = msgget(key, 0644 | IPC_CREAT);

	if (_queueId < 0)
	{
		throw QueueException("Queue cannot be created");
	}

	std::cout << "[Queue successfully created]" << std::endl;
}

int QueueOwner::getId()
{
	return _queueId;
}

} /* namespace core */
