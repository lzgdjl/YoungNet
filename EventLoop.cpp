#include <stdlib.h>
#include <unistd.h>

#include "EventLoop.h"
#include "Channel.h"
#include "Logger.h"

namespace YoungNet
{
	EventLoop::EventLoop()
	{
		epfd_ = epoll_create(1024);
		if (epfd < 0)
		{
			fprintf(stderr, "cannot create epoll fd\n");
			exit(1);
		}

		readyEvent_.reserve(1024);		
	}
	
	EventLoop::~EventLoop()
	{
		close(epfd_);
	}

	void EventLoop::UpdateChannel(Channel* chan)
	{
		int event = 0;
		if (chan->events_ & 1)
		{
			event |= EPOLLIN;
		}
		if (chan->events_ & 2)
		{
			event |= EPOLLOUT;
		}
		
		
		struct epoll_event ev;
		ev.events = event;
		ev.data.ptr = chan;	
		auto it = channelContainer_.find(chan);
		if (it != channelContainer_.end())
		{
			
			if (epoll_ctl(epfd_, EPOLL_CTL_MOD, chan.listenFd_, &ev) != 0)
			{
				LOG_ERROR_WRITE("modify epoll failed. error: %s\n", strerror(errno));
			}
		}
		else
		{
			if (epoll_ctl(epfd_, EPOLL_CTL_ADD, chan.listenFd_, &ev) != 0)
			{
				LOG_ERROR_WRITE("add epoll failed. error: %s\n", strerror(errno));
			}	
		}
	}

	void EventLoop::RemoveChannel(Channel* chan)
	{
		struct epoll_event ev;
		ev.events = event;
		ev.data.ptr = chan;
		if (epoll_ctl(epfd_, EPOLL_CTL_DEL, chan->listenFd_, &ev) != 0)
		{
			LOG_ERROR_WRITE("delete epoll failed. error: %s\n", strerror(errno));
		}
	}
	
	std::vector<Channel*> GetReadyChannel()
	{
		std::vector<Channel*> result;

		int nfds = epoll_wait(epfd_, &*readyEvent_.begin(), readyEvent_.size(), -1);
		if (nfds < 0)
		{
			LOG_ERROR_WRITE("epoll eait return -1\n");
			return result;
		}
		for (int i = 0; i < nfds; ++i)
		{
			Channel* chan = (Channel*)readyEvent_[i].data.ptr;
			chan.revents_ = readyEvent_[i].events;
			result.push_back(chan);
		}

		if (nfds == readyEvent_.size())
		{
			readyEvent_.reserve(readyEvent_.size()*2);
		}
		
		return result;
	}

	void EventLoop::StartLoop()
	{
		while (1)
		{
			std::vector<Channel*> result = GetReadyChannel();
			for (auto it = result.begin(); it != result.end(); ++it)
			{
				it->HandleEvent();
			}
		}
	}
}

