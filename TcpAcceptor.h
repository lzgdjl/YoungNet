#ifndef __YOUNG_NET_TCP_ACCEPTOR_H__
#define __YOUNG_NET_TCP_ACCEPTOR_H__

#include <functional>
#include <stdint.h>

#include "Socket.h"
#include "InetAddr.h"

namespace YoungNet
{

class Channel;
class EventLoop;

class TcpAcceptor
{
public:
	TcpAcceptor(uint16_t port, EventLoop* loop);
	~TcpAcceptor() noexcept;

	TcpAcceptor(const TcpAcceptor&) = delete;
	TcpAcceptor& operator=(const TcpAcceptor&) = delete;
	
	using HandleCallback = std::function<void (int)>;
	void SetReadCallback(const HandleCallback &cb);
	void SetReadCallback(HandleCallback&& cb);

	void Start();

private:
	Channel* chan_;
	InetAddress addr_;
	Socket sock_;
	EventLoop *loop_;
	HandleCallback readCallback_;

//	int Accept();
	int OnRead();
//	int Listen();
};
} // namespace YoungNet

#endif // __YOUNG_NET_TCP_ACCEPTOR_H__
