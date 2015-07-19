#ifndef REQUESTS_ICLIENTMANAGER_H_
#define REQUESTS_ICLIENTMANAGER_H_

#include "coreFwd.h"

#include <memory>

class IClientManager
{
	public:
		virtual ~IClientManager() {};

		virtual void addClient(core::ClientDataPtr clientData) = 0;
		virtual core::ClientDataPtr getClientById(long id) = 0;
		virtual bool isNameValid(std::string name) = 0;
		virtual void removeClient(core::ClientDataPtr clientData) = 0;
		virtual core::ClientDataPtr getClientByName(std::string name) = 0;
};

typedef std::shared_ptr<IClientManager> IClientManagerPtr;

#endif /* REQUESTS_ICLIENTMANAGER_H_ */
