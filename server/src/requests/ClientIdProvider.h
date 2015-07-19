#ifndef REQUESTS_CLIENTIDPROVIDER_H_
#define REQUESTS_CLIENTIDPROVIDER_H_

#include <memory>

class ClientIdProvider
{
	public:
		ClientIdProvider();
		virtual ~ClientIdProvider();

		int getUniqeId()
		{
			return _idCounter++;
		}

	private:
		int _idCounter;
};

typedef std::shared_ptr<ClientIdProvider> ClientIdProviderPtr;

#endif /* REQUESTS_CLIENTIDPROVIDER_H_ */
