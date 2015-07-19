#ifndef CLIENTDATA_H_
#define CLIENTDATA_H_

#include <string>

#include <memory>

namespace core
{

class ClientData
{
	public:
		ClientData();
		ClientData(std::string username,long id);
		virtual ~ClientData();

		bool operator==(const ClientData& d ) const;

		bool operator<(const ClientData& d ) const ;

		volatile long Id;
		std::string Username;
		std::string Channel;
		int RequestId;
};

typedef std::shared_ptr<ClientData> ClientDataPtr;

}

#endif /* CLIENTDATA_H_ */
