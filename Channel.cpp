#include "Channel.h"

namespace YoungNet
{
	Channel::Channel(int fd, EventLoop* loop)
		:listenFd_(fd),
		loop_(loop)
	{
		SetReadCallback(std::bind(DefaultCallback, this));
		SetWriteCallback(std::bind(DefaultCallback, this));
		SetCloseCallback(std::bind(DefaultCallback, this));
	}
	
	
}

