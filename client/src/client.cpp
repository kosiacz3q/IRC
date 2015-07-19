#include <iostream>
#include <thread>

#include <boost/algorithm/string.hpp>

#include "coreFwd.h"

#include "ClientProtocolExecutor.h"

#include "commands/DisconnectCommandHandler.h"
#include "commands/SendMessageCommand.h"
#include "commands/UnknownCommandHandler.h"
#include "commands/ConnectCommandHandler.h"
#include "commands/IRequestResponseManager.h"
#include "commands/ListChannelsCommand.h"
#include "commands/JoinChannelCommand.h"
#include "commands/ListUsersCommandHandler.h"
#include "commands/ICommandRegisterer.h"
#include "commands/LeaveChannelCommandHandler.h"
#include "commands/SendPrivateMessage.h"
#include "commands/AddToFriendsCommandHandler.h"

#include "RequestResponseManager.h"

using namespace std;

int main()
{
	auto clientData = core::ClientDataPtr(new core::ClientData());

	while (clientData->Username.empty())
	{
		std::cout<<"\nInsert name : ";
		std::cin>>clientData->Username;
		boost::trim(clientData->Username);
	}

	std::cout<<"Hello "<< clientData->Username<<"! Try #help to see available commands"<<std::endl;

	auto queueHandler = core::IQueueHandlerPtr(new core::QueueHandler(0));
	auto displayer = core::IDisplayerPtr(new core::ConsoleDisplayer());
	auto responseManager = IRequestResponseManagerPtr(new RequestResponseManager());
	auto messageListenerController = MessageListenerControllerPtr(new MessageListenerController());
	auto notificationsHandler = NotificationsHandlerPtr(new NotificationsHandler(displayer));
	auto clientProtocolExecutor = ClientProtocolExecutorPtr(new ClientProtocolExecutor(queueHandler, displayer, responseManager, clientData,messageListenerController,notificationsHandler));

	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new UnknownCommandHandler(displayer,clientProtocolExecutor)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new DisconnectCommandHandler(clientData, displayer, queueHandler,responseManager,clientProtocolExecutor,messageListenerController)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new ConnectCommandHandler(clientData, queueHandler, displayer,responseManager,clientProtocolExecutor,messageListenerController)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new ListChannelsCommand(clientData, displayer , queueHandler, responseManager)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new JoinChannelCommand(responseManager, displayer, queueHandler, clientData)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new ListUsersCommandHandler(clientData, displayer , queueHandler, responseManager)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new LeaveChannelCommandHandler(responseManager, displayer, queueHandler, clientData)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new SendMessageCommand(queueHandler, clientData, displayer, responseManager)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new SendPrivateMessage(queueHandler, clientData, displayer, responseManager)));
	clientProtocolExecutor->registerCommand(ICommandHandlerPtr(new AddToFriendsCommandHandler(clientData,displayer,queueHandler,responseManager)));

	std::thread logicExecutorThread = std::thread(&ClientProtocolExecutor::execute, &(*clientProtocolExecutor));

	std::string lastCommand = "";
	bool toExit = false;

	while (!toExit)
	{
		getline(std::cin , lastCommand);

		clientProtocolExecutor->addCommand(lastCommand);

		if (lastCommand.compare("#exit") == 0)
		{
			toExit = true;
			continue;
		}
	}

	logicExecutorThread.join();

	std::cout << "[Client ends]" << std::endl;

	return 0;
}
