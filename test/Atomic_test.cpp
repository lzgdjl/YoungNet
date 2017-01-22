#include <assert.h>
#include <stdio.h>

#include "Atomic.h"

using namespace YoungNet;

int main()
{
	AtomicInt32 value;
	assert(value.Get() == 0);
	assert(value.GetAndAdd(1) == 0);
	assert(value.Get() == 1);

	assert(value.AddAndGet(1) == 2);
	assert(value.Get() == 2);
	
	assert(value.IncAndGet() == 3);
	
	assert(value.DecAndGet() == 2);
	
	value.Add(10);
	assert(value.Get() == 12);
	
	value.GetAndSet(5);
	assert(value.Get() == 5);

	printf("all tests passed\n");

	return 0;
}

