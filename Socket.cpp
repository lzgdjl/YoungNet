#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <unistd.h>

#include "Socket.h"
#include "InetAddr.h"
#include "Logger.h"

namespace YoungNet
{
	Socket::Socket(int fd)
		: sockfd_(fd)
	{
	}

	Socket::~Socket()
	{
		close(sockfd_);
	}

	void Socket::Bind(const InetAddress& addr)
	{
		int ret = ::bind(sockfd_, reinterpret_cast<const sockaddr*>(&addr.GetInetAddr()),
						static_cast<socklen_t>(sizeof(struct sockaddr_in)));
		if (ret < 0)
		{
			LOG_FATAL("bind failed, error: %s", strerror(errno));
		}
	}

	void Socket::Listen()
	{
		int ret = ::listen(sockfd_, SOMAXCONN);
		if (ret < 0)
		{
			LOG_FATAL("listen failed, error: %s", strerror(errno));
		}
	}

	int Socket::Accept(InetAddress* peer)
	{
	retry:
		struct sockaddr_in sa;
		memset(&sa, 0, sizeof(sa));

		socklen_t len = sizeof(sa);
		
		int fd = accept4(sockfd_, reinterpret_cast<sockaddr*>(&sa), &len,
					SOCK_NONBLOCK|SOCK_CLOEXEC);
		
		if (fd < 0)
		{
			if (errno == EAGAIN || errno == ECONNABORTED)
				goto retry;
		}
		else
		{
			peer->SetSockAddr(sa);
		}
		return fd;
	}

	void Socket::SetTcpNoDelay()
	{
		int value = 1;
		::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
	}

	void Socket::SetReuseAddr()
	{
		int value = 1;
		::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	}

	void Socket::SetReusePort()
	{
		int value = 1;
		::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value));
	}

	void Socket::SetKeepAlive()
	{
		int value = 1;
		::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &value, sizeof(value));
	}

	int Socket::CreateSocketNonblock()
	{
		int fd = ::socket(AF_INET, SOCK_NONBLOCK|SOCK_CLOEXEC|SOCK_STREAM, IPPROTO_TCP);
		if (fd < 0)
		{
			LOG_FATAL("socket failed, error: %s", strerror(errno));
		}
		return fd;
	}

	int Socket::Connect(int fd, const struct sockaddr_in& sa)
	{
		return ::connect(fd, reinterpret_cast<const sockaddr*>(&sa), sizeof(sa));
	}

	struct sockaddr_in Socket::GetSocketAddr(int fd)
	{
		struct sockaddr_in sa;
		memset(&sa, 0, sizeof(sa));
		
		socklen_t len = sizeof(sa);	
		if (::getsockname(fd, reinterpret_cast<sockaddr*>(&sa), &len) < 0)
		{
			LOG_WARN_WRITE("getsockname failed, error: %s", strerror(errno));
		}
		return sa;
	}

	struct sockaddr_in Socket::GetLocalSocketAddr(int fd)
	{
		return GetSocketAddr(fd);
	}

	struct sockaddr_in Socket::GetPeerSocketAddr(int fd)
	{
		struct sockaddr_in sa;
		memset(&sa, 0, sizeof(sa));
		socklen_t len = sizeof(sa);

		if (::getpeername(fd, reinterpret_cast<sockaddr*>(&sa), &len) < 0)
		{
			LOG_WARN_WRITE("getpeername failed, error: %s", strerror(errno));
		}

		return sa;
	}
}

