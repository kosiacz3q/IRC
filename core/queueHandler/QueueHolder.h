#ifndef QUEUEHANDLER_QUEUEHOLDER_H_
#define QUEUEHANDLER_QUEUEHOLDER_H_

#include "../contract/IQueueIdProvider.h"

namespace core
{

class QueueHolder : public IQueueIdProvider
{
	public:
		QueueHolder(key_t key);
		virtual ~QueueHolder();

		int getId();

	private:
		int _queueId;

};

} /* namespace core */

#endif /* QUEUEHANDLER_QUEUEHOLDER_H_ */
