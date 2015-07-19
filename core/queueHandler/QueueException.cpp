#include "QueueException.h"

namespace core
{

QueueException::QueueException(std::string reason)
	:_reason(reason)
{

}

QueueException::~QueueException()
{

}

const char* QueueException::what() const throw()
{
	return _reason.c_str();
}


}
