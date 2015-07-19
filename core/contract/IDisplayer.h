#ifndef CONTRACT_IDISPLAYER_H_
#define CONTRACT_IDISPLAYER_H_

#include <string>
#include <memory>

namespace core
{

class IDisplayer
{
	public:
		virtual ~IDisplayer() {};
		virtual void displayLine(std::string msg) = 0;
};

typedef std::shared_ptr<IDisplayer> IDisplayerPtr;

} /* namespace core */

#endif /* CONTRACT_IDISPLAYER_H_ */
