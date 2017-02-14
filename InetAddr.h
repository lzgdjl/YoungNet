#ifndef __YOUNG_NET_NET_ADDRESS_H__
#define __YOUNG_NET_NET_ADDRESS_H__

#include <arpa/inet.h>
#include <netinet.h>
#include <string>
#include <stdint.h>

namespace YoungNet
{
	class InetAddress
	{
	public:
		using uint16_t Port;
		explicit InetAddress(Port port);
		InetAddress(const std::string& ip, Port port);
		InetAddress(const sockaddr_in& inet);

		void SetSockAddr(const sockaddr_in& inet);
		
		Port Port() const;
		std::string Ip() const;
		const struct sockaddr_in& GetInetAddr() const;

	private:
		struct sockaddr_in sk_;
	};
} // namespace YoungNet

#endif // __YOUNG_NET_NET_ADDRESS_H__

