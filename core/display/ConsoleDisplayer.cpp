#include "ConsoleDisplayer.h"

#include <iostream>

namespace core
{

ConsoleDisplayer::ConsoleDisplayer()
{


}

ConsoleDisplayer::~ConsoleDisplayer()
{

}


void ConsoleDisplayer::displayLine(std::string msg)
{
	std::cout<<msg<<std::endl;
}

} /* namespace core */
