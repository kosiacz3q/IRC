#ifndef CLIENTSMANAGER_H_
#define CLIENTSMANAGER_H_

#include <vector>
#include <memory>

#include "coreFwd.h"

#include "requests/IClientManager.h"

class ClientsManager : public IClientManager
{
	public:
		ClientsManager();
		virtual ~ClientsManager();

		core::ClientDataPtr getClientById(long id);

		void addClient(core::ClientDataPtr clientData);

		bool isNameValid(std::string name);

		void removeClient(core::ClientDataPtr clientData);

		core::ClientDataPtr getClientByName(std::string name);
	private:
		std::vector<core::ClientDataPtr> _clients;

};

typedef std::shared_ptr<ClientsManager> ClientsManagerPtr;

#endif /* CLIENTSMANAGER_H_ */
