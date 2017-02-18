#ifndef __YOUNG_NET_NET_ADDRESS_H__
#define __YOUNG_NET_NET_ADDRESS_H__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <stdint.h>

namespace YoungNet
{
	class InetAddress
	{
	public:
		using PortType = uint16_t;
		explicit InetAddress(PortType port);
		InetAddress(const std::string& ip, PortType port);
		InetAddress(const sockaddr_in& inet);

		void SetSockAddr(const sockaddr_in& inet);
		
		PortType Port() const;
		std::string Ip() const;
		const struct sockaddr_in& GetInetAddr() const;

	private:
		struct sockaddr_in sk_;
	};
} // namespace YoungNet

#endif // __YOUNG_NET_NET_ADDRESS_H__

