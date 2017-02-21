#ifndef __YOUNG_NET_BUFFER_H__
#define __YOUNG_NET_BUFFER_H__

#include <vector>

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

// Thanks to github.com/zhihu/kids

namespace YoungNet
{
	class Buffer
	{
		friend bool operator<(const Buffer& lhs, const Buffer& rhs);
		friend bool operator==(const Buffer& lhs, const Buffer& rhs);
	
	public:
		Buffer(const char* data, size_t size);
		explicit Buffer(size_t size);
		Buffer();
		explicit Buffer(const char* str);
		Buffer(const Buffer& other);
		Buffer(Buffer&& other);
		~Buffer();

		Buffer& operator=(const Buffer& other);
		Buffer& operator=(Buffer&& rhs);
		
		Buffer* PopFront(size_t size);
		void RemoveFront(size_t size);
		
		char* Data(size_t pos=0);
		const char* Data(size_t pos=0) const;
		size_t Hash() const;

		char* Blank();
		
		size_t Size() const;
		void SetSize(size_t size);
		size_t BlankSize() const;
		size_t Capacity() const;
		

		bool Append(const char* data, size_t size);
		void Clear();
		size_t Resize(size_t size);
		bool Reserve(size_t size);
		
		void AppendPrintf(const char* fmt, ...);
		void AppendVaprintf(const char* fmt, va_list ap);

		class HashHelp
		{
		public:
			size_t operator()(const Buffer& buf) const
			{
				return buf.Hash();
			}
		};

	private:
		void DeepCopy(const Buffer& other);
		void DeepCopy(Buffer&& other);
		void Free();
		void Clone();


		char* data_;
		size_t size_;
		size_t capacity_;	
	};
} // namespace YoungNet

#endif // __YOUNG_NET_BUFFER_H__

