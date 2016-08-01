//#include <Network/src/Unix/SocketBE_Unix.hpp>
#include "SocketBE_Unix.hpp"
#include <errno.h>
#include <fcntl.h>
#include <cstring>

namespace wv {
namespace be {

    sockaddr_in SocketBE::createAddress(intU32 l_address, unsigned short l_port) {
        sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_addr.s_addr	= htonl(l_address);
        addr.sin_family			= AF_INET;
        addr.sin_port			= htons(l_port);

        return addr;
    }

    SocketHandle SocketBE::invalidSocket() {
        return -1;
    }

    void SocketBE::close(SocketHandle l_socket) {
        ::close(l_socket);
    }

    void SocketBE::setBlocking(SocketHandle l_socket, bool l_block) {
        int status = fcntl(l_socket, F_GETFL);
        if(l_block){
            fcntl(l_socket, F_SETFL, status & ~O_NONBLOCK);
        }
        else{
            fcntl(l_socket, F_SETFL, status | ~O_NONBLOCK);
        }
    }

    Socket::Status SocketBE::getErrorStatus() {
        if((errno == EAGAIN) || (errno == EINPROGRESS))
            return Socket::NotReady;

        switch (errno)
        {
            case EWOULDBLOCK:   	return Socket::NotReady;
            case ECONNABORTED:		return Socket::NotReady;
            case ECONNRESET:    	return Socket::Disconnected;
            case ETIMEDOUT: 		return Socket::Disconnected;
            case ENETRESET: 		return Socket::Disconnected;
            case ENOTCONN:  		return Socket::Disconnected;
            case EPIPE:     		return Socket::Disconnected;
            default:				return Socket::Error;
        }
    }
}
}
