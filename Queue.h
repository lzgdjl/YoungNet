#ifndef __YOUNG_NET_QUEUE_H__
#define __YOUNG_NET_QUEUE_H__

#include <vector>

#include "Mutex.h"
#include "CondVar.h"

namespace YoungNet
{
	template <typename T>
	class Queue
	{
	public:
		using BlockQueue = std::vector<T>;
	
	private:
		Mutex mutex_;
		CondVar cond_;
		BlockQueue queue_;

	public:
		Queue()
			: mutex_(),
				cond_(mutex_)
		{
			
		}

		void Put(const T& item)
		{
			MutexGuard lock(mutex_);
			queue_.push_back(item);
			cond_.Notify();			
		}

		void Put(T&& item)
		{
			MutexGuard lock(mutex_);
			queue_.push_back(std::move(item));
			cond_.Notify();
		}

		void Get(T& item)
		{
			MutexGuard lock(mutex_);

			while (queue_.empty())
			{
				cond_.Wait();
			}
			auto it = queue_.begin();
			item = *it;
			queue_.erase(it);
		}
		
		size_t Size()
		{
			MutexGuard lock(mutex_);
			return queue_.size();
		}
	};
} // namespace YoungNet

#endif // __YOUNG_NET_QUEUE_H__

