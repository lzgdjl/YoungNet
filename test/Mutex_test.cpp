#include <assert.h>
#include <stdio.h>

#include "Mutex.h"

using namespace YoungNet;

int main()
{
	Mutex mtx;
	assert(mtx.IsLocked() == false);
	
	{
		MutexGuard lock(mtx);
		assert(mtx.IsLocked() == true);
		
	}
	assert(mtx.IsLocked() == false);
	

	printf("all tests passed\n");
	return 0;
}

