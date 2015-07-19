#ifndef REQUESTRESPONSEMANAGER_H_
#define REQUESTRESPONSEMANAGER_H_

#include <map>

#include "commands/IRequestResponseManager.h"

class RequestResponseManager: public IRequestResponseManager
{
	public:
		RequestResponseManager();
		virtual ~RequestResponseManager();

		void registerResponseType(int requestId, std::string responseHandler);
		std::string getHandler(int request);

	private:
		std::map<int, std::string> _requestToResponse;
};

#endif /* REQUESTRESPONSEMANAGER_H_ */
