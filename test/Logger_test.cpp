#include "Logger.h"

using namespace YoungNet;

int main()
{
	LOG_DEBUG_WRITE("Hello, World");
	LOG_ERROR_WRITE("Hello, World");
	LOG_TRACE_WRITE("Hello, World");
	LOG_WARN_WRITE("Hello, World");

	printf("all tests passed\n");

	return 0;
}
