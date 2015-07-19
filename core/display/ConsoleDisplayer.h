#ifndef DISPLAY_CONSOLEDISPLAYER_H_
#define DISPLAY_CONSOLEDISPLAYER_H_

#include "../contract/IDisplayer.h"

namespace core
{

class ConsoleDisplayer : public IDisplayer
{
	public:
		ConsoleDisplayer();
		virtual ~ConsoleDisplayer();

		void displayLine(std::string msg);
};

} /* namespace core */

#endif /* DISPLAY_CONSOLEDISPLAYER_H_ */
