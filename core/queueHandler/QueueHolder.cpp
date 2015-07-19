#include "QueueHolder.h"

#include <sys/msg.h>

#include "QueueException.h"

namespace core
{

QueueHolder::QueueHolder(key_t key)
{
	_queueId = msgget(key, 0644);

	if (_queueId < 0)
	{
		throw QueueException("Queue does not exists\n");
	}
}

QueueHolder::~QueueHolder()
{

}

int QueueHolder::getId()
{
	return _queueId;
}

} /* namespace core */
