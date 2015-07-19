#ifndef CONTRACT_IQUEUEIDPROVIDER_H_
#define CONTRACT_IQUEUEIDPROVIDER_H_

#include <memory>

namespace core
{

class IQueueIdProvider
{
	public:
		virtual ~IQueueIdProvider() {};
		virtual int getId() = 0;
};

typedef std::shared_ptr<IQueueIdProvider> IQueueIdProviderPtr;

} /* namespace core */

#endif /* CONTRACT_IQUEUEIDPROVIDER_H_ */
