#include <iostream>
#include <thread>

#include <coreFwd.h>

#include "queueHandler/QueueHandler.h"

#include "requests/UnknownRequestHandler.h"
#include "requests/ConnectionRequestHandler.h"
#include "requests/DisconnectionRequestHandler.h"
#include "requests/ListChannelsRequest.h"
#include "requests/JoinChannelRequest.h"
#include "requests/LeaveChannelRequestHandler.h"
#include "requests/ListUsersInChannelRequestHandel.h"
#include "requests/SendMessageRequestHandler.h"
#include "requests/NotificationCounter.h"
#include "requests/SendPrivateMessageRequestHandler.h"
#include "requests/AddFriendRequestHandler.h"
#include "requests/FriendManager.h"

#include "ServerLogicExecutor.h"
#include "ChannelManager.h"
#include "ClientsManager.h"

int main()
{
	int address;
	std::cout<<"Set server address : ";
	std::cin>>address;

	auto queueHandler = core::QueueHandlerPtr(new core::QueueHandler(core::IQueueIdProviderPtr(new core::QueueOwner(address))));
	auto clientsManager = std::shared_ptr<ClientsManager> (new ClientsManager());
	auto displayer = core::IDisplayerPtr(new core::ConsoleDisplayer());
	auto channelManager = ChannelManagerPtr(new ChannelManager());
	auto notificationCounter = NotificationCounterPtr(new NotificationCounter());
	auto notifiationSender = MessagesSenderPtr(new MessagesSender(queueHandler, displayer, notificationCounter));
	auto clientIdProvider = ClientIdProviderPtr(new ClientIdProvider());
	auto friendManager = FriendManagerPtr(new FriendManager(notifiationSender));

	ServerLogicExecutor serverLogicExecutor = ServerLogicExecutor(queueHandler,displayer,clientsManager);

	channelManager->addChannel("Global");
	channelManager->addChannel("it");

	displayer->displayLine("Registering handlers");

	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new UnknownRequestHandler(queueHandler, displayer)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new ConnectionRequestHandler(queueHandler, clientsManager, displayer,clientIdProvider,friendManager)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new DisconnectionRequestHandler(queueHandler, displayer, channelManager, clientsManager,friendManager)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new ListChannelsRequest(displayer ,channelManager ,queueHandler)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new JoinChannelRequest(channelManager , clientsManager , queueHandler, displayer) ));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new LeaveChannelRequestHandler(channelManager , clientsManager , queueHandler, displayer) ));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new ListUsersInChannelRequestHandel(displayer ,channelManager ,queueHandler)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new SendMessageRequestHandler(displayer, channelManager, queueHandler, clientsManager, notifiationSender)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new SendPrivateMessageRequestHandler(displayer, queueHandler, clientsManager, notifiationSender)));
	serverLogicExecutor.registerHandler(IRequestHandlerPtr(new AddFriendRequestHandler(clientsManager,queueHandler,displayer, friendManager)));

	displayer->displayLine("Starting server");

	std::thread logicExecutorThread = std::thread(&ServerLogicExecutor::execute, &serverLogicExecutor);

	displayer->displayLine("Server is up and running");

	std::string lastCommand = "";
	bool toExit = false;

	while (!toExit)
	{
		displayer->displayLine("Waiting for command");
		getline(std::cin , lastCommand);

		if (lastCommand.compare("#exit") == 0)
		{
			displayer->displayLine("Exit request");
			toExit = true;
			serverLogicExecutor.stop();
			continue;
		}
	}

	logicExecutorThread.join();

	std::cout << "[Server end]" << std::endl;
	return 0;
}
