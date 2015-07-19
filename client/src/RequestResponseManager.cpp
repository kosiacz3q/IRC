#include "RequestResponseManager.h"

RequestResponseManager::RequestResponseManager()
	:_requestToResponse(std::map<int, std::string>())
{

}

RequestResponseManager::~RequestResponseManager()
{

}

void RequestResponseManager::registerResponseType(int requestId, std::string responseHandler)
{
	_requestToResponse.insert(std::pair<int, std::string>(requestId, responseHandler));
}

std::string RequestResponseManager::getHandler(int request)
{
	auto result = _requestToResponse.find(request);

	if (result == _requestToResponse.end())
		return "";
	else
		return result->second;
}
