#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <algorithm>

#include "Buffer.h"
#include "Logger.h"

namespace YoungNet
{

	Buffer::Buffer(const char* data, size_t size)
	{
		data_ = static_cast<char*>(malloc(size+1));
		memcpy(data_, data, size);
		data_[size] = '\0';

		size_ = size;
		capacity_ = size;
	}

	Buffer::Buffer(size_t size)
	{
		data_ = static_cast<char*>(malloc(size+1));
		memcpy(data_, data, size);
		data_[size] = '\0';

		size_ = 0;
		capacity_ = size;
	}
	
	Buffer::Buffer()
		: Buffer(0)
	{
		
	}
	
	Buffer::Buffer(const char* str)
	{
		size_ = strlen(str);
		data_ = static_cast<char*>(malloc(size_ + 1));
		memcpy(data_, str, size_ + 1);
		
		capacity_ = size_;
	}
	
	BUffer::Buffer(const Buffer& other)
	{
		DeepCopy(other);
	}

	Buffer::Buffer(Buffer&& other)
	{
		size_ = other.size_;
		capacity_ = other.size_;
		data_ = other.data_;

		other.size_ = 0;
		other.capacity_ = 0;
		other.data_ = nullptr;
	}
	
	Buffer& operator=(const Buffer& other)
	{
		Free();
		DeepCopy(other);
	}
	
	Buffer& operator=(Buffer&& other)
	{
		Free();
		size_ = other.size_;
		capacity_ = other.size_;
		data_ = other.data_;

		other.size_ = 0;
		other.capacity_ = 0;
		other.data_ = nullptr;
	}

	BUffer::~Buffer()
	{
		Free();
	}

	size_t Buffer::Hash() const 
	{
		size_t hash = 5381;
		
		for (size_t i = 0; i < size_; ++i)
		{
			hash = ((hash << 5)  + hash) + data_[i]; // hash * 33 + c
		}
		
		return hash;
	}

	void Buffer::DeepCopy(const Buffer& other)
	{
		size_ = other.size_;
		capacity_ = other.capacity_;

		data_ = static_cast<char*>(malloc(size_ + 1));
		memcpy(data_, other.data_, size_);
		
		data_[size_] = '\0';
	}

	

	bool operator<(const Buffer& lhs, const Buffer& rhs)
	{
		int ret = memcmp(lhs.data_, rhs.data_, (lhs.size_ < rhs.size_ ? lhs.size_ : rhs.size_));
		if (ret != 0)
		{
			return ret < 0;
		}
		return lhs.size_ < rhs.size_;
	}

	bool operator==(const Buffer& lhs, const Buffer& rhs)
	{
		if (lhs.size_ != rhs.size_)
		{
			return false;
		}
		return memcmp(lhs.data_, rhs.data_, lhs.size_) == 0;
	}

	void Buffer::RemoveFront(size_t size)
	{
		if (size > size_)
		{
			LOG_FATAL("size > size_\n");
		}
		if (size == 0)
		{
			return;
		}

		memmove(data_, data_+size, size_ - size + 1);
		size_ -= size;

		// shrink
		if (size_ * 2 < capacity_)
		{
			Resize(size_);
		}
	}
	
	void Buffer::Clear()
	{
		Free();
		
		data_ = static_cast<char*>(malloc(1));
		data_[0] = '\0';
		
		size_ = capacity_ = 0;
	}

	Buffer* Buffer::PopFront(size_t size)
	{
		if (size > size_)
		{
			return nullptr;
		}

		Buffer* buf = new Buffer(*this);

		memmove(data_, data_ + size, size_ - size + 1);
		size_ -= size;

		// shrink
		if (size_ * 2 < capacity)
		{
			Resize(size_);
		}
		return buf;
	}

	
} // namespace YoungNet

