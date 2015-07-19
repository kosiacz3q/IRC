#ifndef IREQUESTHANDLER_H_
#define IREQUESTHANDLER_H_

#include <memory>

#include "jsonParserFwd.h"

class IRequestHandler
{
	public:
		virtual ~IRequestHandler(){};

		virtual void handleRequest(rapidjson::Document& doc) = 0;

		virtual std::string getType() = 0;
};

typedef std::shared_ptr<IRequestHandler> IRequestHandlerPtr;

#endif /* IREQUESTHANDLER_H_ */
