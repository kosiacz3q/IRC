#ifndef CONTRACT_IQUEUEHANDLER_H_
#define CONTRACT_IQUEUEHANDLER_H_

#include <memory>
#include <string>

#include "IQueueIdProvider.h"

namespace core
{

class IQueueHandler
{
	public:
		virtual ~IQueueHandler() {};

		virtual void send(long type,const std::string& message) = 0;
		virtual std::string getMessage(int type) = 0;
		virtual void setQueueProvider(IQueueIdProviderPtr queueIdProvider) = 0;
};

typedef std::shared_ptr<IQueueHandler> IQueueHandlerPtr;


}

#endif /* CONTRACT_IQUEUEHANDLER_H_ */
