#include "Channel.h"
#include "EventLoop.h"

namespace YoungNet
{
	#define READ_LISTEN 1
	#define WRITE_LISTEN 2

	Channel::Channel(int fd, EventLoop* loop)
		:listenFd_(fd),
		loop_(loop),
		events_(0),
		revents_(0)
	{
		SetReadCallback(std::bind(DefaultCallback, this));
		SetWriteCallback(std::bind(DefaultCallback, this));
		SetCloseCallback(std::bind(DefaultCallback, this));
	}
	
	
	void Channel::EnableRead()
	{
		events_ |= READ_LISTEN;
		loop_->UpdateChannel(this);
	}

	void Channel::EnableWrite()
	{
		events_ |= WRITE_LISTEN;
		loop_->UpdateChannel(this);
	}

	void Channel::EnableAll()
	{
		events_ |= READ_LISTEN;
		events_ |= WRITE_LISTEN;
		loop_->UpdateChannel(this);
	}

	void Channel::DisableRead()
	{
		events_ &= ~READ_LISTEN;
		loop_->UpdateChannel(this);	
	}

	void Channel::DisableWrite()
	{
		events_ &= ~WRITE_LISTEN;
		loop_->UpdateChannel(this);
	}

	void Channel::DisableAll()
	{
		events_ = 0;
		loop_->UpdateChannel(this);
	}

	void Channel::RemoveListen()
	{
		loop_->RemoveChannel(this);
	}
	
	
	void Channel::SetReadCallback(const HandleCallback &callback)
	{
		readCallback_ = callback;
	}
	
	void Channel::SetReadCallback(HandleCallback &&callback)
	{
		readCallback_ = std::move(callback);
	}

	void Channel::SetWriteCallback(const HandleCallback& callback)
	{
		writeCallback_ = callback;
	}
	
	void Channel::SetWriteCallback(HandleCallback&& callback)
	{
		readCallback_ = std::move(callback);
	}

    void Channel::SetCloseCallback(const HandleCallback& callback)
	{
		closeCallback_ = callback;
	}

	void Channel::SetCloseCallback(HandleCallback&& callback)
	{
		closeCallback_ = std::move(callback);
	}

    void Channel::HandleRead()
	{
		if (readCallback_ < 0)
		{
			closeCallback_;
		}
	}	

	void Channel::HandleWrite()
	{
		if (writeCallback_ < 0)
		{
			closeCallback_;
		}
	}

	void Channel::HandleClose()
	{
		closeCallback_;
	}

	void Channel::HandleError()
	{
		closeCallback_;
	}
}

