#ifndef __YOUNG_NET_LOGGER_H__
#define __YOUNG_NET_LOGGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Thread.h"
#include "Util.h"

namespace YoungNet
{
	enum LogLevel
	{
		NOTICE, TRACE, DEBUG, WARN, ERROR
	};
	

//	extern LogLevel g_LogLevel;

	LogLevel GetLogLevel();// { return g_LogLevel; }
	void SetLogLevel(LogLevel level);// { g_LogLevel = level; }

	#define LOG_NOTICE_WRITE(fmt, ...) if(GetLogLevel() <= LogLevel::NOTICE) \
		fprintf(stderr, "[NOTICE][%s:%d][%d][%s]" fmt "\n", __FILE__, __LINE__, Thread::GetTid(), ReadableTime().c_str(), ##__VA_ARGS__)
	#define LOG_TRACE_WRITE(fmt, ...) if(GetLogLevel() <= LogLevel::TRACE) \
		fprintf(stderr, "[TRACE ][%s:%d][%d][%s]" fmt "\n", __FILE__, __LINE__, Thread::GetTid(), ReadableTime().c_str(), ##__VA_ARGS__)
	#define LOG_DEBUG_WRITE(fmt, ...) if (GetLogLevel() <= LogLevel::DEBUG) \
		fprintf(stderr, "[DEBUG ][%s:%d][%d][%s]" fmt "\n", __FILE__, __LINE__, Thread::GetTid(), ReadableTime().c_str(), ##__VA_ARGS__)
	#define LOG_WARN_WRITE(fmt, ...) if (GetLogLevel() <= LogLevel::WARN) \
		fprintf(stderr, "[WARN  ][%s:%d][%d][%s]" fmt "\n", __FILE__, __LINE__, Thread::GetTid(), ReadableTime().c_str(), ##__VA_ARGS__)
	#define  LOG_ERROR_WRITE(fmt, ...) if (GetLogLevel() <= LogLevel::ERROR) \
		fprintf(stderr, "[ERROR ][%s:%d][%d][%s]" fmt "\n", __FILE__, __LINE__, Thread::GetTid(), ReadableTime().c_str(), ##__VA_ARGS__)

} // namespace YoungNet

#endif // __YOUNG_NET_LOGGER_H__

