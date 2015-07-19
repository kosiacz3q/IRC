#ifndef REQUESTS_UNKNOWNREQUESTHANDLER_H_
#define REQUESTS_UNKNOWNREQUESTHANDLER_H_

#include "IRequestHandler.h"

#include "coreFwd.h"

class UnknownRequestHandler: public IRequestHandler
{
	public:
		UnknownRequestHandler(core::IQueueHandlerPtr queueHandler, core::IDisplayerPtr displayer);

		virtual ~UnknownRequestHandler();

		void handleRequest(rapidjson::Document& doc);

		std::string getType();

	private:
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;
};

#endif /* REQUESTS_UNKNOWNREQUESTHANDLER_H_ */
