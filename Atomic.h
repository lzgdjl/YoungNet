#ifndef __YOUNG_NET_ATOMIC_H__
#define __YOUNG_NET_ATOMIC_H__

#include <stdint.h>

namespace YoungNet
{
	template <typename T>
	class AtomicT
	{
	private:
		volatile T value_;

	public:
		AtomicT()
			: value_(0)
		{
		}
		
		AtomicT(const AtomicT&) = delete;
		AtomicT& operator=(const AtomicT&) = delete;
		AtomicT(AtomicT&&) = delete;
		AtomicT& operator=(AtomicT&&) = delete;

		T Get()
		{
			return __sync_val_compare_and_swap(&value_, 0, 0);
		}
		
		T GetAndAdd(T x)
		{
			return __sync_fetch_and_add(&value_, x);
		}

		T AddAndGet(T x)
		{
			return GetAndAdd(x) + x;
		}

		T IncAndGet()
		{
			return AddAndGet(1);
		}
		
		T DecAndGet()
		{
			return AddAndGet(-1);
		}

		void Add(T x)
		{
			GetAndAdd(x);
		}

		void Inc()
		{
			IncAndGet();
		}

		void Dec()
		{
			DecAndGet();
		}
		
		T GetAndSet(T newValue)
		{
			return __sync_lock_test_and_set(&value_, newValue);
		}
	};

	using AtomicInt32 = AtomicT<int32_t>;
	using AtomicInt64 = AtomicT<int64_t>;
} // namespace YoungNet

#endif // __YOUNG_NET_ATOMIC_H__

