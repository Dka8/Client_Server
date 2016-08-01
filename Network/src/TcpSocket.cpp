#include "../include/TcpSocket.hpp"
#include "../include/IpAddress.hpp"
#include "SocketBE.hpp"

namespace {
    #ifdef SYSTEM_LINUX
        const int flags = MSG_NOSIGNAL;
    #else
        const int flags = 0;
    #endif
}

namespace wv{
    TcpSocket::TcpSocket() :
        Socket(Tcp)
    {}

    unsigned short TcpSocket::getLocalPort() const {
        if (GetHandle() != be::SocketBE::invalidSocket())
        {
            sockaddr_in address;
            be::SocketBE::AddrLength size = sizeof(address);
            if (getsockname(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
            {
                return ntohs(address.sin_port);
            }
        }
        return 0;
    }

    IpAddress TcpSocket::getRemoteAddress() const {
        if (GetHandle() != be::SocketBE::invalidSocket())
        {
            sockaddr_in address;
            be::SocketBE::AddrLength size = sizeof(address);
            if (getpeername(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
            {
                return IpAddress(ntohl(address.sin_addr.s_addr));
            }
        }
        return IpAddress::None;
    }

    unsigned short TcpSocket::getRemotePort() const {
        if (GetHandle() != be::SocketBE::invalidSocket())
        {
            sockaddr_in address;
            be::SocketBE::AddrLength size = sizeof(address);
            if (getpeername(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
            {
                return ntohs(address.sin_port);
            }
        }
        return 0;
    }

    Socket::Status TcpSocket::Connect(const IpAddress& remoteAddress, unsigned short remotePort) {
        Create();
        sockaddr_in address = be::SocketBE::createAddress(remoteAddress.toInteger(), remotePort);

        if (::connect(GetHandle(), reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1)
            return be::SocketBE::getErrorStatus();

        return Done;
    }

    void TcpSocket::Disconnect()
    {
        Close();
    }

    Socket::Status TcpSocket::Send(const void* data, std::size_t size)
    {
        std::size_t sent;
        return Send(data, size, sent);
    }

    Socket::Status TcpSocket::Send(const void* data, std::size_t size, std::size_t& sent)
    {
        if (!data || (size == 0))
        {
            return Error;
        }

        int result = 0;
        for (sent = 0; sent < size; sent += result)
        {
            result = ::send(GetHandle(), static_cast<const char*>(data) + sent, size - sent, flags);
            if (result < 0)
            {
                Status status = be::SocketBE::getErrorStatus();
                if ((status == NotReady) && sent)
                    return Partial;

                return status;
            }
        }
        return Done;
    }

    Socket::Status TcpSocket::Receive(void* data, std::size_t size, std::size_t& received)
    {
        received = 0;
        if (!data)
        {
            return Error;
        }
        int sizeReceived = recv(GetHandle(), static_cast<char*>(data), static_cast<int>(size), flags);
        if (sizeReceived > 0)
        {
            received = static_cast<std::size_t>(sizeReceived);
            return Done;
        }
        else if (sizeReceived == 0)
        {
            return Socket::Disconnected;
        }
        else
        {
            return be::SocketBE::getErrorStatus();
        }
    }
}

