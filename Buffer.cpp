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
		data_[size] = '\0';

		size_ = 0;
		capacity_ = size;
	}
	
	Buffer::Buffer()
	{
		data_ = static_cast<char*>(malloc(1));
		data_[0] = '\0';
	
		size_ = 0;
		capacity_ = 0;
	}
	
	Buffer::Buffer(const char* str)
	{
		size_ = strlen(str);
		data_ = static_cast<char*>(malloc(size_ + 1));
		memcpy(data_, str, size_ + 1);
		
		capacity_ = size_;
	}
	
	Buffer::Buffer(const Buffer& other)
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
	
	Buffer& Buffer::operator=(const Buffer& other)
	{
		Free();
		DeepCopy(other);
	
		return *this;
	}
	
	Buffer& Buffer::operator=(Buffer&& other)
	{
		Free();
		size_ = other.size_;
		capacity_ = other.size_;
		data_ = other.data_;

		other.size_ = 0;
		other.capacity_ = 0;
		other.data_ = nullptr;

		return *this;
	}

	Buffer::~Buffer()
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

		data_ = static_cast<char*>(malloc(capacity_ + 1));
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
		if (size_ * 2 < capacity_)
		{
			Resize(size_);
		}
		return buf;
	}
	
	bool Buffer::Append(const char* data, size_t size)
	{
		if (size <= 0)
		{
			return true;
		}

		if (Reserve(size_ + size))
		{
			memcpy(data_ + size_, data, size);
			size_ += size;

			data_[size_] = '\0';
			return true;
		}
		
		LOG_ERROR_WRITE("no mem\n");
		return false;
	}

	void Buffer::AppendPrintf(const char* fmt, ...)
	{
		va_list ap;

		va_start(ap, fmt);
		AppendVaprintf(fmt, ap);
		va_end(ap);
	}

	void Buffer::AppendVaprintf(const char* fmt, va_list ap)
	{
		va_list cpy;
		char* buf = nullptr;
		size_t buflen = 16;

		while (1)
		{
			buf = static_cast<char*>(malloc(buflen));
			if (buf == NULL)
			{
				LOG_ERROR_WRITE("error append vaprintf: %d", buflen);
				return;
			}
			buf[buflen - 2] = '\0';
			va_copy(cpy, ap);
			vsnprintf(buf, buflen, fmt, cpy);
			if (buf[buflen - 2] != '\0')
			{
				free(buf);
				buflen *= 2;
				continue;
			}
			break;
		}

		Append(buf, strlen(buf));
		free(buf);
	}
	
	bool Buffer::Reserve(size_t size)
	{
		if (size < capacity_) return true;
		
		size_t s = std::max(2*capacity_, size);
		return Resize(s) >= s;
	}

	size_t Buffer::Resize(size_t size)
	{
		char* buf = static_cast<char*>(realloc(data_, size+1));
		if (buf)
		{
			data_ = buf;
			capacity_ = size;
			data_[capacity_] = '\0';
		}
		else
		{
			LOG_ERROR_WRITE("Resize error\n");
		}

		return capacity_;
	}

	char* Buffer::Data(size_t pos) 
	{
		return data_ + pos;
	}
	
	const char* Buffer::Data(size_t pos) const
	{
		return data_ + pos;
	}

	size_t Buffer::Size()  const
	{
		return size_;
	}
	
	void Buffer::SetSize(size_t size)
	{
		size_ = size;
	}

	size_t Buffer::BlankSize() const
	{
		return capacity_ - size_;
	}

	size_t Buffer::Capacity() const
	{
		return capacity_;
	}

	
} // namespace YoungNet

