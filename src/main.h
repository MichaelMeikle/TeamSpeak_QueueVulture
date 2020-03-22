#include <string>
#include <memory>
#include "teamspeak.h"
#include "log.h"

class Vulture
{
public:
	static std::string kPluginName;
	static std::string kPluginAuthor;
	static std::string kPluginDescription;
	static std::string kPluginVersion;
	
	Vulture();
	void ChangeChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
	void CommandEvent(uint64 serverConnectionHandlerID, std::string command);
	void ResetLock();
	void set_selected_item(uint64 item_id) { selected_item_id_ = item_id; }
private:
	std::unique_ptr<Log> console_;
	bool lock_set_;
	/* Server ID of channel ID that is being watched */
	uint64 server_id_;
	/* Channel ID that is being watched */
	uint64 locked_channel_id_;
	/* Item that is currently selected in TeamSpeak, Client, Channel, or Server */
	uint64 selected_item_id_ = 0;
	int client_count_max_ = 0;
};