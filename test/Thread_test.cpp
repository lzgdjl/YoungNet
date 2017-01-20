#include <unistd.h>

#include "Thread.h"

using namespace YoungNet;

void process()
{
	printf("a new thread is running thread id is %d\n", (int)Thread::GetTid());
}

int main()
{
	Thread thread(process);
	
	thread.Start();
	printf("main thread tid is %d\n", (int)Thread::GetTid());
	printf("main thread exit\n");
	sleep(3);

	printf("all tests passed\n");

	return 0;
}


