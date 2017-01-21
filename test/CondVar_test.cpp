#include <stdio.h>

#include "CondVar.h"

using namespace YoungNet;

int main()
{
	Mutex mutex;
	CondVar cond(mutex);

	printf("all tests passed\n");

	return 0;
}

