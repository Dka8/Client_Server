#include "UdpSocket.h"
#include "Socket.h"

namespace wv {
	UdpSocket::UdpSocket() : Socket(Udp) {

	}

	unsigned short UdpSocket::getLocalPort() const {
		if (GetHandle() != be::SocketBE::invalidSocket()) {
			sockaddr_in	address;
			be::SocketBE::AddrLength size = sizeof(address);
			if (getsockname(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1) {
				return ntohs(address.sin_port);
			}
		}
		return 0;
	}

	Socket::Status UdpSocket::Bind(unsigned short l_port, const IpAddress& l_address) {
		Create();
		if ((l_address == IpAddress::None) || (l_address == IpAddress::Broadcast))
			return Error;

		sockaddr_in addr = be::SocketBE::createAddress(l_address.toInteger(), l_port);
		if (::bind(GetHandle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
			return Error;
		}
		return Done;
	}

	void UdpSocket::Unbind() {
		Close();
	}

	Socket::Status UdpSocket::Send(const void* l_data, std::size_t l_size,
		const IpAddress& l_remoteAddress, unsigned short l_remotePort) {
		Create();
		if (l_size > MaxDatagramSize) {
			return Error;
		}

		sockaddr_in address = be::SocketBE::createAddress(l_remoteAddress.toInteger(), l_remotePort);
		int sent = sendto(GetHandle(), static_cast<const char*>(l_data), static_cast<int>(l_size),
			0, reinterpret_cast<sockaddr*>(&address), sizeof(address));

		if (sent < 0)
			return be::SocketBE::getErrorStatus();
		return Done;
	}

	Socket::Status UdpSocket::Receive(void* l_data, std::size_t l_size,
		std::size_t& l_received, IpAddress& l_remoteAddress, unsigned short& l_remotePort) {
		l_received = 0;
		l_remoteAddress = IpAddress();
		l_remotePort = 0;

		if (!l_data)
		{
			return Error;
		}

		sockaddr_in address = be::SocketBE::createAddress(INADDR_ANY, 0);

		be::SocketBE::AddrLength addressSize = sizeof(address);
		int sizeReceived = recvfrom(GetHandle(), static_cast<char*>(l_data),
			static_cast<int>(l_size), 0, reinterpret_cast<sockaddr*>(&address), &addressSize);

		if (sizeReceived < 0)
			return be::SocketBE::getErrorStatus();

		l_received = static_cast<std::size_t>(sizeReceived);
		l_remoteAddress = IpAddress(ntohl(address.sin_addr.s_addr));
		l_remotePort = ntohs(address.sin_port);

		return Done;
	}
}
