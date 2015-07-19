#ifndef CLIENTPROTOCOLEXECUTOR_H_
#define CLIENTPROTOCOLEXECUTOR_H_

#include <list>
#include <map>
#include <memory>
#include <thread>

#include "developFwd.h"
#include "coreFwd.h"

#include "commands/ICommandHandler.h"
#include "commands/IRequestResponseManager.h"
#include "commands/MessageListenerController.h"
#include "notifications/NotificationsHandler.h"

#include "commands/ICommandRegisterer.h"

class ClientProtocolExecutor : public IMessageListener, public ICommandRegisterer
{
	public:
		ClientProtocolExecutor(
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer,
				IRequestResponseManagerPtr requestResponseManager,
				core::ClientDataPtr clientData,
				MessageListenerControllerPtr messageController,
				NotificationsHandlerPtr notificationsHandler
				);
		virtual ~ClientProtocolExecutor();
		void execute();

		void addCommand(std::string command);

		void registerCommand(ICommandHandlerPtr handler );
		std::vector<std::string> getCommands();

		void startReading();
		void stopReading();

	private:
		void readRoutine();

		std::string getCommand();

		void handleCommand(std::string command);

		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;

		volatile bool _running;
		volatile bool _reading;

		core::AtomicContainer<std::string> _pendingCommands;

		bool isReadingEnable();

		int _requestCounter;

		std::map<std::string, ICommandHandlerPtr> _commandToHandler;
		std::shared_ptr<std::thread> _readerThreadPtr;
		IRequestResponseManagerPtr _requestResponseManager;
		core::ClientDataPtr _clientData;
		MessageListenerControllerPtr _messageController;
		NotificationsHandlerPtr _notificationsHandler;

};

typedef std::shared_ptr<ClientProtocolExecutor> ClientProtocolExecutorPtr;

#endif /* CLIENTPROTOCOLEXECUTOR_H_ */
