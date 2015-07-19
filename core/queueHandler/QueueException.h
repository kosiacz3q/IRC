#ifndef QUEUEHANDLER_QUEUEEXCEPTION_H_
#define QUEUEHANDLER_QUEUEEXCEPTION_H_

#include <exception>
#include <string>

namespace core
{

class QueueException : public std::exception
{
	public:
		QueueException(std::string reason);
		virtual ~QueueException() throw();

		virtual const char* what() const throw();

	private:
		std::string _reason;
};

} /* namespace core */

#endif /* QUEUEHANDLER_QUEUEEXCEPTION_H_ */
