#ifndef __YOUNG_NET_CHANNEL_H__
#define __YOUNG_NET_CHANNEL_H__

#include <functional>

namespace YoungNet
{
	
	class EventLoop;
	class Channel
	{
	friend class EventLoop;
	public:
		Channel(int fd, EventLoop*);
		Channel(const Channel&) = delete;
		Channel(Channel&&) = delete;
		Channel& operator=(const Channel&) = delete;
		Channel& operator=(Channel&&) = delete;
		
		void EnableRead();
		void EnableWrite();
		void EnableAll();
		
		void DisableRead();
		void DisableWrite();
		void DisableAll();
		void RemoveListen();
		

		using HandleCallback = std::function<int()>;

		void SetReadCallback(const HandleCallback&);
		void SetReadCallback(HandleCallback&&);
		
		void SetWriteCallback(const HandleCallback&);
		void SetWriteCallback(HandleCallback&&);

		void SetCloseCallback(const HandleCallback&);
		void SetCloseCallback(HandleCallback&&);
		
	
		void HandleRead();
		void HandleWrite();
		void HandleClose();
		void HandleError();
		void HandleEvent();
	
	private:
		int DefaultCallback();
		int listenFd_;
		EventLoop *loop_;
		int events_;
		int revents_;

		HandleCallback readCallback_;
		HandleCallback writeCallback_;
		HandleCallback closeCallback_;
	};
} // namespace YoungNet

#endif // __YOUNG_NET_CHANNEL_H__

