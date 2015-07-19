#ifndef SERVERLOGICEXECUTOR_H_
#define SERVERLOGICEXECUTOR_H_

#include <map>

#include "developFwd.h"
#include "coreFwd.h"
#include "jsonParserFwd.h"

#include "requests/IRequestHandler.h"
#include "requests/IClientManager.h"

class ServerLogicExecutor
{
	public:
		ServerLogicExecutor(
				core::IQueueHandlerPtr queueHandler,
				core::IDisplayerPtr displayer,
				IClientManagerPtr clientManager);

		virtual ~ServerLogicExecutor();

		void execute();

		void registerHandler(IRequestHandlerPtr handler);

		void stop();

	private:
		core::IQueueHandlerPtr _queueHandler;
		core::IDisplayerPtr _displayer;

		std::map<std::string, IRequestHandlerPtr> _requestTypeToHandler;

		bool _running;

		const std::string _exitString = "123475631233215gsd";

		IClientManagerPtr _clientManager;
};

#endif /* SERVERLOGICEXECUTOR_H_ */
