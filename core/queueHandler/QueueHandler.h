#ifndef QUEUEHANDLER_QUEUEHANDLER_H_
#define QUEUEHANDLER_QUEUEHANDLER_H_

#include <memory>

#include "../contract/IQueueHandler.h"
#include "../contract/IQueueIdProvider.h"

namespace core
{

class QueueHandler: public IQueueHandler
{
	public:
		QueueHandler();
		QueueHandler(IQueueIdProviderPtr queueIdProvider);
		virtual ~QueueHandler();

		std::string getMessage(int type);
		void send(long  type, const std::string& message);

		void setQueueProvider(IQueueIdProviderPtr queueIdProvider);

	private:
		int _queueId;
		IQueueIdProviderPtr _queueIdProvider;
};

typedef std::shared_ptr<QueueHandler> QueueHandlerPtr;

}
/* namespace core */

#endif /* QUEUEHANDLER_QUEUEHANDLER_H_ */
