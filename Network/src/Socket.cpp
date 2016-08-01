//#include <Network/include/Socket.hpp>
//#include <Network/src/SocketBE.hpp>
#include "../include/Socket.hpp"
#include "SocketBE.hpp"
#include <iostream>

namespace wv {

    Socket::Socket(Type l_type) :
        m_type			(l_type),
        m_socket		(be::SocketBE::invalidSocket()),
        m_isBlocking	(true)
    {}

    Socket::~Socket() { Close(); }

    void Socket::SetBlocking(bool l_blocking) {
        if (m_socket != be::SocketBE::invalidSocket())
            be::SocketBE::setBlocking(m_socket, l_blocking);

        m_isBlocking = l_blocking;
    }

    bool Socket::isBlocking() const { return m_isBlocking; }

    SocketHandle Socket::GetHandle() const { return m_socket; }

    void Socket::Create() {
        if (m_socket == be::SocketBE::invalidSocket()) {
            SocketHandle handle = socket(PF_INET, m_type == Tcp ? SOCK_STREAM : SOCK_DGRAM, 0);

            if (handle == be::SocketBE::invalidSocket()) {
                //err() << "Failed to create socket" << std::endl;
                return;
            }
            Create(handle);
        }
    }

    void Socket::Create(SocketHandle l_handle) {
        if (m_socket == be::SocketBE::invalidSocket()) {
            m_socket = l_handle;
            SetBlocking(m_isBlocking);

            if (m_type == Tcp) {
                int yes = 1;
                if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY,
                    reinterpret_cast<char*>(&yes), sizeof(yes)) == -1) {
                    //err() << "Failed to set socket option \"TCP_NODELAY\" ; "
                    //	<< "all your TCP packets will be buffered" << std::endl;
                }

				#if !defined(SYSTEM_WINDOWS)
                if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEPORT,
                    reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
                {
                    std::cout << "Failed to enable reuse port" << std::endl;
                }
				#endif
            }
            else {
                // Enable broadcast by default for UDP sockets
                int yes = 1;
                if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST,
                    reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
                {
                    //err() << "Failed to enable broadcast on UDP socket" << std::endl;
                }
				#if !defined(SYSTEM_WINDOWS)
                if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEPORT,
                    reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
                {
                    std::cout << "Failed to enable reuse port" << std::endl;
                }
				#endif
                //if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR,
                //    reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
                //{
                //    //err() << "Failed to enable broadcast on UDP socket" << std::endl;
                //}
            }
        }
    }

    void Socket::Close() {
        if(m_socket != be::SocketBE::invalidSocket()) {
            be::SocketBE::close(m_socket);
            m_socket = be::SocketBE::invalidSocket();
        }
    }
}
