#ifndef __YOUNG_NET_MUTEX_H__
#define __YOUNG_NET_MUTEX_H__

#include <pthread.h>

namespace YoungNet
{

class CondVar;

class Mutex
{
public:
    Mutex();
    ~Mutex() noexcept;
   
    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;
    Mutex(Mutex&&) = delete;
    Mutex& operator=(Mutex&&) = delete;      
                                         
    void Lock() noexcept;
    void UnLock() noexcept;
	bool IsLocked() noexcept;
private:
	friend class CondVar;
    pthread_mutex_t mutex_;
	bool locked_;

};

class MutexGuard
{
public:
    explicit MutexGuard(Mutex&);
    ~MutexGuard() noexcept;
    
	MutexGuard(const MutexGuard&) = delete;
	MutexGuard& operator=(const MutexGuard&)= delete;
	MutexGuard(Mutex&&) = delete;
	MutexGuard& operator=(MutexGuard&&) = delete;
                   
private:
    Mutex &mutex_;
};
}

#endif // __YOUNG_NET_MUTEX_H__


