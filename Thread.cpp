#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <assert.h>
#include <functional>

#include "Thread.h"

using namespace YoungNet;

namespace
{
	__thread pid_t __cached_tid = 0;
}

static pid_t CacheTid()
{
	if (__cached_tid == 0)
	{
		__cached_tid = ::syscall(SYS_gettid);
	}
	return __cached_tid;
}

Thread::Thread(const BGJobs& job)
	: started_(false),
		pid_(0),
		job_(job)
{
	
}

Thread::Thread(BGJobs&& job)
	: started_(false),
		pid_(0),
		job_(std::move(job))
{

}

Thread::~Thread() noexcept
{
	if (started_)
	{
		pthread_detach(pid_);
	}
}

namespace 
{
	struct ThreadHelper
	{
		Thread::BGJobs job;
	};
}

static void* BGJobProc(void* arg)
{
	ThreadHelper* thread = reinterpret_cast<ThreadHelper*>(arg);
	try
	{
		thread->job();
		delete thread;
		return NULL;
	}
	catch(...)
	{
		return NULL;
	}
}

void Thread::Start()
{
	ThreadHelper* help = new ThreadHelper;
	help->job = job_;

	assert(!started_);
	started_ = true;
	pthread_create(&pid_, NULL, &BGJobProc, help);
}

pid_t Thread::GetTid()
{
	return CacheTid();
}


