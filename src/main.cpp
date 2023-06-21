#include "main.h"
#include <vector>
#include <sstream>

std::string Vulture::kPluginName = "TS Queue Vulture";
std::string Vulture::kPluginAuthor = "Michael Meikle";
std::string Vulture::kPluginDescription = "Queue snatcher script";
std::string Vulture::kPluginVersion = "0.0.2";

Vulture::Vulture()
{
	console_ = std::make_unique<Log>(FN);
	console_->Info(LN, "Vulture Initialized");

	lock_set_ = false;
	server_id_ = 0;
	locked_channel_id_ = 0;
}

void Vulture::ChangeChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage)
{
	if (serverConnectionHandlerID == server_id_ && lock_set_)
	{
		anyID my_id = 0;
		ts3()->getClientID(serverConnectionHandlerID, &my_id);
		if (oldChannelID == locked_channel_id_)
		{
			anyID* client_list;
			ts3()->getChannelClientList(serverConnectionHandlerID, locked_channel_id_, &client_list);
			int i = 0;
			while (client_list[i]) i++;
			if (i < client_count_max_ || client_count_max_ == -1)
			{
				ts3()->requestClientMove(server_id_, my_id, locked_channel_id_, "", NULL);
				console_->PrintMsg(serverConnectionHandlerID, "User left watched channel, vultching initiated", PLUGIN_MESSAGE_TARGET_CHANNEL);
			}
		}
		else if (newChannelID == locked_channel_id_)
		{
			if (my_id == clientID)
			{
				lock_set_ = false;
				server_id_ = 0;
				locked_channel_id_ = 0;
				console_->PrintMsg(serverConnectionHandlerID, "You vultched channel the channel, clearing lock", PLUGIN_MESSAGE_TARGET_CHANNEL);
			}
		}
	}
}

void Vulture::CommandEvent(uint64 serverConnectionHandlerID, std::string command)
{
	//Splits the command by spaces into the args vector
	std::stringstream ss(command); std::string token;
	std::vector<std::string> args;
	while (std::getline(ss, token, ' '))
	{
		args.push_back(token);
		console_->Debug(LN, "Array Size: " + std::to_string(args.size()) + " Token: " + token);
	}

	if (args[0].compare("unlock") == 0 || args[0].compare("clear") == 0)
	{
		lock_set_ = false;
		server_id_ = 0;
		locked_channel_id_ = 0;
		console_->PrintMsg(serverConnectionHandlerID, "Channel lock removed on " + std::to_string(locked_channel_id_), PLUGIN_MESSAGE_TARGET_CHANNEL);
	}
	else if (args[0].compare("lock") == 0)
	{
		if (validate_channel(serverConnectionHandlerID, selected_item_id_))
		{
			lock_set_ = true;
			locked_channel_id_ = selected_item_id_;
			int result = 4;
			if (args.size() <= 1)
			{
				ts3()->getChannelVariableAsInt(serverConnectionHandlerID, selected_item_id_, CHANNEL_MAXCLIENTS, &result);
				client_count_max_ = result;
			}
			else
			{
				try 
				{
					client_count_max_ = std::stoi(args[1]);
				}
				catch (const std::exception & e)
				{
					console_->PrintMsg(serverConnectionHandlerID, "[color=red]Invalid 2nd client arguement[/color]", PLUGIN_MESSAGE_TARGET_CHANNEL);
					client_count_max_ = result;
				}
			}

			server_id_ = serverConnectionHandlerID;
			console_->PrintMsg(serverConnectionHandlerID, "Channel lock set to " + std::to_string(locked_channel_id_) + " with max client count of " + std::to_string(client_count_max_), PLUGIN_MESSAGE_TARGET_CHANNEL);
			ChangeChannelEvent(serverConnectionHandlerID, -1, locked_channel_id_, 0, true, nullptr);
		}
		else
			console_->PrintMsg(serverConnectionHandlerID, "[color=red] Channel lock attempted on item: " + std::to_string(selected_item_id_) + " but not a valid channel id [/color]", PLUGIN_MESSAGE_TARGET_CHANNEL);
	}
	else if (args[0].compare("status") == 0)
	{
		char* result;
		ts3()->getChannelVariableAsString(serverConnectionHandlerID, locked_channel_id_, CHANNEL_NAME, &result);
		if (lock_set_)
			console_->PrintMsg(serverConnectionHandlerID, "Channel Lock Status:\nChannel ID: " + std::to_string(locked_channel_id_)
				+ "\nChannel Name: " + std::string(result), PLUGIN_MESSAGE_TARGET_CHANNEL);
		else
			console_->PrintMsg(serverConnectionHandlerID, "Channel Lock Status: [color=red]Off[/color]", PLUGIN_MESSAGE_TARGET_CHANNEL);
	}
}