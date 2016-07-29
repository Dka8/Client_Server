#include "TcpSocket.h"

namespace wv{
    TcpListener::TcpListener() :
        Socket(Tcp)
        {}

    unsigned short TcpListener::getLocalPort() const
    {
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

    Socket::Status TcpListener::Listen(unsigned short port, const IpAddress& address)
    {
        Create();

        if ((address == IpAddress::None) || (address == IpAddress::Broadcast))
            return Error;

        sockaddr_in addr = be::SocketBE::createAddress(address.toInteger(), port);
        if (bind(GetHandle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
        {
            return Error;
        }
        if (::listen(GetHandle(), 0) == -1)
        {
            return Error;
        }
        return Done;
    }

    void TcpListener::Close()
    {
        Socket::Close();
    }

    Socket::Status TcpListener::Accept(TcpSocket& socket)
    {
        if (GetHandle() == be::SocketBE::invalidSocket())
        {
            return Error;
        }

        sockaddr_in address;
        be::SocketBE::AddrLength length = sizeof(address);
        SocketHandle remote = ::accept(GetHandle(), reinterpret_cast<sockaddr*>(&address), &length);

        if (remote == be::SocketBE::invalidSocket())
            return be::SocketBE::getErrorStatus();

        socket.Close();
        socket.Create(remote);

        return Done;
    }
}
