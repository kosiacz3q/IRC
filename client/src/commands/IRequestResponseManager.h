#ifndef COMMANDS_IREQUESTRESPONSEMANAGER_H_
#define COMMANDS_IREQUESTRESPONSEMANAGER_H_

#include <string>
#include <memory>

class IRequestResponseManager
{
	public:
		virtual ~IRequestResponseManager() {};

		virtual void registerResponseType(int requestId, std::string responseHandler) = 0;
		virtual std::string getHandler(int request) = 0;
};

typedef std::shared_ptr<IRequestResponseManager> IRequestResponseManagerPtr;


#endif /* COMMANDS_IREQUESTRESPONSEMANAGER_H_ */
