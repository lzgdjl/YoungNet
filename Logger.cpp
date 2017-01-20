#include "Logger.h"

namespace YoungNet
{
	LogLevel g_LogLevel = LogLevel::TRACE;
	
	LogLevel GetLogLevel() { return g_LogLevel; }
	void SetLogLevel(LogLevel level) { g_LogLevel = level; }
}

