#include "../SocketBE.hpp"
#include <cstring>

namespace wv {
    namespace be {
        sockaddr_in SocketBE::createAddress(intU32 l_address, intU16 l_port) {
            sockaddr_in addr;
            std::memset(&addr, 0, sizeof(addr));
            addr.sin_addr.s_addr	= htonl(l_address);
            addr.sin_family			= AF_INET;
            addr.sin_port			= htons(l_port);

            return addr;
        }

        SocketHandle SocketBE::invalidSocket() {
            return INVALID_SOCKET;
        }

        void SocketBE::close(SocketHandle l_socket) {
            closesocket(l_socket);
        }

        void SocketBE::setBlocking(SocketHandle l_socket, bool l_block) {
            u_long blocking = l_block ? 0 : 1;
            ioctlsocket(l_socket, FIONBIO, &blocking);
        }

        Socket::Status SocketBE::getErrorStatus() {
            switch (WSAGetLastError())
            {
                case WSAEWOULDBLOCK:	return Socket::NotReady;
                case WSAEALREADY:		return Socket::NotReady;
                case WSAECONNABORTED:	return Socket::Disconnected;
                case WSAECONNRESET:		return Socket::Disconnected;
                case WSAETIMEDOUT:		return Socket::Disconnected;
                case WSAENETRESET:		return Socket::Disconnected;
                case WSAENOTCONN:		return Socket::Disconnected;
                case WSAEISCONN:		return Socket::Done;
                default:				return Socket::Error;
            }
        }

        struct SocketInitializer
        {
            SocketInitializer() {
                WSADATA	init;
                WSAStartup(MAKEWORD(2, 2), &init);
            }
            ~SocketInitializer() {
                WSACleanup();
            }
        };
        SocketInitializer globalInitializer;
    }
}
