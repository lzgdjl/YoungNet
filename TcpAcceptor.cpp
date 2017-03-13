#include "TcpAcceptor.h"
#include "EventLoop.h"
#include "InetAddr.h"
#include "Channel.h"

namespace YoungNet
{
	TcpAcceptor::TcpAcceptor(uint16_t port, EventLoop* loop)
	: chan_(nullptr),
		addr_(port),
		sock_(Socket::CreateSocketNonblock()),
		loop_(loop)
	{
		sock_.Bind(addr_);
		sock_.SetTcpNoDelay();
		sock_.Listen();
		
		chan_ = new Channel(sock_.Fd(), loop_);		
	}
	
	TcpAcceptor::~TcpAcceptor()
	{
		delete chan_;
	}

	void TcpAcceptor::SetReadCallback(const HandleCallback& cb)
	{
		readCallback_ = cb;
	}

	void TcpAcceptor::SetReadCallback(HandleCallback&& cb)
	{
		readCallback_ = std::move(cb);
	}
	
	void TcpAcceptor::Start()
	{
		chan_->SetReadCallback(std::bind(&TcpAcceptor::OnRead, this));
		chan_->EnableRead();
	}

	int TcpAcceptor::OnRead()
	{
		InetAddress addr(0);
		
		while (1)
		{
			int fd = sock_.Accept(&addr);
			if (fd > 0)
			{
				readCallback_(fd);
			}
			else
			{
				break;
			}
		}

		return 0;
	}
} // namespace YoungNet

