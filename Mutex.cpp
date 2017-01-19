#include "Mutex.h"

namespace YoungNet
{
	Mutex::Mutex()
	{
		pthread_mutex_init(&mutex_, NULL);
		locked_ = false;
	}
	
	Mutex::~Mutex() noexcept
	{
		pthread_mutex_destroy(&mutex_);
	}

	void Mutex::Lock() noexcept
	{
		pthread_mutex_lock(&mutex_);
		locked_ = true;
	}
	void Mutex::UnLock() noexcept
	{
		pthread_mutex_unlock(&mutex_);
		locked_ = false;
	}
	
	bool Mutex::IsLocked() noexcept
	{
		return locked_;
	}

	MutexGuard::MutexGuard(Mutex& mtx)
	: mutex_(mtx)
	{
		mutex_.Lock();
	}
	
	MutexGuard::~MutexGuard() noexcept
	{
		mutex_.UnLock();
	}
}
