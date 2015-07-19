#ifndef QUEUEHANDLER_QUEUEOWNER_H_
#define QUEUEHANDLER_QUEUEOWNER_H_

#include "../contract/IQueueIdProvider.h"

namespace core
{

class QueueOwner : public IQueueIdProvider
{
	public:
		virtual ~QueueOwner();
		QueueOwner(key_t key);

		int getId();

	private:
		int _queueId;
};

} /* namespace core */

#endif /* QUEUEHANDLER_QUEUEOWNER_H_ */
