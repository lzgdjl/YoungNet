#ifndef __YOUNG_NET_THREAD_H__
#define __YOUNG_NET_THREAD_H__

#include <functional>
#include <pthread.h>

namespace YoungNet
{
	class Thread
	{
	public:
		typedef std::function<void()> BGJobs;

		explicit Thread(const BGJobs&);
		explicit Thread(BGJobs&&);
		~Thread() noexcept;

		void Start();
		static pid_t GetTid();
		
		Thread(const Thread&) = delete;
		Thread& operator=(const Thread&) = delete;
		Thread(Thread&&) = delete;
		Thread& operator=(Thread&&) = delete;
	
	private:
		bool started_;
		pthread_t pid_;
		BGJobs job_;
	};
} // namespace YoungNet

#endif // __YOUNG_NET_NET_THREAD+H__

