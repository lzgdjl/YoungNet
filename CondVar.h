#ifndef __YOUNG_NET_CONDVAR_H__
#define __YOUNG_NET_CONDVAR_H__

#include "Mutex.h"
#include <time.h>

namespace YoungNet
{
	class CondVar
	{
	public:
		explicit CondVar(Mutex& mutex);
		~CondVar() noexcept;
		
		CondVar(const CondVar&) = delete;
		CondVar& operator=(const CondVar&) = delete;
		
		CondVar(CondVar&&) = delete;
		CondVar& operator=(CondVar&&) = delete;
		
		void Wait();
		bool WaitTimeout(time_t seconds);
		void Notify();
		void NotifyAll();
		
	private:
		pthread_cond_t cond_;
		Mutex& mutex_;
	};
} // namespace YoungNet

#endif // __YOUNG_NET_CONDVAR_H__

