#ifndef CHANNELMANAGER_H_
#define CHANNELMANAGER_H_

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Channel.h"


class ChannelManager
{
	public:
		ChannelManager();
		virtual ~ChannelManager();

		void addChannel(std::string name);

		ChannelPtr getChannelByName(std::string name);

		void removeChannelByName(std::string name);

		std::vector<std::string> getChannelsNames();

	private:

		std::map<std::string, ChannelPtr> _channelsMap;
};

typedef std::shared_ptr<ChannelManager> ChannelManagerPtr;

#endif /* CHANNELMANAGER_H_ */
