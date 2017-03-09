#ifndef __YOUNG_NET_EVENTLOOP_H__
#define __YOUNG_NET_EVENTLOOP_H__

#include <vector>
#include <set>

struct epoll_event;

namespace YoungNet
{

	class Channel;

	class EventLoop
	{
	public:
		EventLoop();
		~EventLoop() noexcept;

		EventLoop(const EventLoop&) = delete;
		EventLoop(EventLoop&&)= delete;
		EventLoop& operator=(const EventLoop&) = delete;
		EventLoop& operator=(EventLoop&&) = delete;
		
		void UpdateChannel(const Channel*);
		void RemoveChannel(const Channel*);
		void StartLoop();

	private:
		std::vector<Channel*> GetReadyChannel();

		int epfd_;
		std::vector<struct epoll_event> readyEvent_;
		std::set<Channel*> channelContainer_;				
	};
} // namespace YoungNet

#endif // __YOUNG_NET_EVENTLOOP_H__

