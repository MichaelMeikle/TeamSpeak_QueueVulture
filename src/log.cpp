//Local Headers
#include "log.h"

int Log::log_level_ = LogLevel_DEVEL;
bool Log::initialized_ = false;

Log::Log()
{
	file_name_ = "Unknown";
}
Log::Log(int log_level, std::string file_name)
{
	log_level_ = log_level;
	file_name_ = file_name;
}
Log::Log(std::string file_name)
{
	file_name_ = file_name;
}
Log::~Log()
{
}

void Log::PrintMsg(uint64 server_id, std::string msg, enum PluginMessageTarget target)
{
	msg.insert(0, "[color=orange][Queue Vulture] ");
	msg.append("[/color]");
	ts3()->printMessage(server_id, msg.c_str(), target);
	printf("[%s] %s\n", ts3plugin_name(), msg.c_str());
}

void Log::Devel(int line, std::string msg)
{
	if (log_level_ >= LogLevel_DEVEL)
	{
		CommonLog(line, msg, LogLevel_DEVEL);
	}
}

void Log::Info(int line, std::string msg)
{
	if (log_level_ >= LogLevel_INFO)
	{
		CommonLog(line, msg, LogLevel_INFO);
	}
}

void Log::Debug(int line, std::string msg)
{

	if (log_level_ >= LogLevel_DEBUG)
	{
		CommonLog(line, msg, LogLevel_DEBUG);
	}
}

void Log::Warning(int line, std::string msg)
{
	if (log_level_ >= LogLevel_WARNING)
	{
		CommonLog(line, msg, LogLevel_WARNING);
	}
}

void Log::Error(int line, std::string msg)
{
	if (log_level_ >= LogLevel_ERROR)
	{
		CommonLog(line, msg, LogLevel_ERROR);
	}
}

void Log::Critical(int line, std::string msg)
{
	if (log_level_ >= LogLevel_CRITICAL)
	{
		CommonLog(line, msg, LogLevel_CRITICAL);
	}
}

void Log::CommonLog(int line, std::string msg, enum LogLevel level)
{
	msg.append(" | " + file_name_ + " Line Number: " + std::to_string(line));
	ts3()->logMessage(msg.c_str(), level, ts3plugin_name(), 0);
	printf("[%s] %s\n", ts3plugin_name(), msg.c_str());
}
