#include <errno.h>

#include "CondVar.h"

namespace YoungNet
{
	CondVar::CondVar(Mutex& mutex)
		: mutex_(mutex)
	{
		pthread_cond_init(&cond_, NULL);
	}
	CondVar::~CondVar()
	{
		pthread_cond_destroy(&cond_);
	}

	void CondVar::Wait()
	{
		pthread_cond_wait(&cond_, &mutex_.mutex_);
	}

	bool CondVar::WaitTimeout(time_t seconds)
	{
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		
		ts.tv_sec += seconds;
		return ETIMEDOUT == pthread_cond_timedwait(&cond_, &mutex_.mutex_, &ts);
	}

	void CondVar::Notify()
	{
		pthread_cond_signal(&cond_);
	}

	void CondVar::NotifyAll()
	{
		pthread_cond_broadcast(&cond_);
	}
} // namespace YoungNet

