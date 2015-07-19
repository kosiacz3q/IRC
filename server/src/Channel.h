#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <memory>
#include <list>
#include <string>

#include "coreFwd.h"

class Channel
{
	public:
		Channel(std::string name)
			:Clients(std::list<core::ClientDataPtr>()), Name(name)
		{

		}

		virtual ~Channel(){}

		void addClient(core::ClientDataPtr clientData)
		{
			Clients.push_back(clientData);
			clientData->Channel = Name;
		}

		void removeClient(core::ClientDataPtr clientData)
		{
			Clients.remove(clientData);
			clientData->Channel = "";
		}

		std::list<core::ClientDataPtr> Clients;

		std::string Name;
};

typedef std::shared_ptr<Channel> ChannelPtr;

#endif /* CHANNEL_H_ */
