#include "InetAddr.h"
#include "Logger.h"

namespace YoungNet
{
	InetAddress::InetAddress(const struct sockaddr_in& inet)
		: sk_(inet)
	{
	}

	InetAddress::InetAddress(PortType port)
	{
		memset(&sk_, 0, sizeof(sk_));
		sk_.sin_family = AF_INET;
		sk_.sin_addr.s_addr = INADDR_ANY;
		sk_.sin_port = htons(port);
	}

	InetAddress::InetAddress(const std::string& ip, PortType port)
	{
		memset(&sk_, 0, sizeof(sk_));
		inet_addr_.sin_family = AF_INET;
		inet_addr_sin_port = htons(port);
		::inet_pton(AF_INET, ip.c_str(), &sk_.sin_addr);
	}

	InetAddress::PortType Port() const
	{
		return ntohs(sk_.sin_port);
	}
	
	std::string Ip() const 
	{
		char ip[32];
		::inet_ntop(AF_INET, &sk_.sin_addr, ip, sizeof(ip));
		return ip;
	}

	const struct sockaddr_in& GetSockAddr() const
	{
		return sk_;
	}
}

