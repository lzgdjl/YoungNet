#include <sys/time.h>

#include "Util.h"

namespace YoungNet
{
	std::string ReadableTime()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		
		struct tm tm1;
		localtime_r(&tv.tv_sec, &tm1);
		char buffer[512];
		snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
			tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec, (int)(tv.tv_usec/1000));
		return std::string(buffer);
	}
}

