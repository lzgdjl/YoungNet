#include "Logger.h"
#include "Queue.h"
#include "Thread.h"
#include <assert.h>
#include <unistd.h>

using namespace YoungNet;

Queue<int> g_queue;

void PrintItem()
{
	for (int i = 0; i < 100; ++i)
	{
		int item = 0;
		g_queue.Get(item);
		assert(item == i);
		
	}
}

int main()
{
	Thread thread(PrintItem);
	thread.Start();

	for (int i = 0; i < 100; ++i)
	{
		g_queue.Put(i);
	}
	
	sleep(20);
	printf("all tests passed\n");
	return 0;
}

