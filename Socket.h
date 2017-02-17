#ifndef __YOUNG_NET_SOCKET_H__
#define __YOUNG_NET_SOCKET_H__

#include <netinet/in.h>

namespace YoungNet
{
	class InetAddress;
	class Socket
	{
	public:
		Socket(int fd);
		~Socket();
		
		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;
		
		void Bind(const InetAddress& addr);
		void Listen();
		int Accept(InetAddress* peer);
		
		void SetTcpNoDelay(bool option);
		void SetReuseAddr(bool option);
		void SetReusePort(bool option);
		void SetKeepAlive(bool option);
		
		int Fd() const;
		
		static int CreateSocketNonBlock();
		static int Connect(int fd, const struct sockaddr_in& peer);
		static struct sockaddr_in GetSocketAddr(int sockfd);
		static struct sockaddr_in GetLocalSocketAddr(int fd);
		static struct sockaddr_in GetPeerSocketAddr(int fd);
	
	private:
		const int sockfd_;
	};
} // namespace YoungNet

#endif // __YOUNG_NET_SOCKET_H__

