#ifndef NETWORK_SOCKETBE_UNIX_H
#define NETWORK_SOCKETBE_UNIX_H
//#include <Network/include/Socket.hpp>
#include "../../include/Socket.hpp"
#include "../../include/SafeTypes.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

namespace wv {
namespace be {

    //вспомогательный класс для работы напрямую с Berkeley Sockets
    //все медоты в данном классе сокетонезависимы
    class SocketBE {
    public:
        typedef socklen_t AddrLength;

        //возвращает специфическую Berkeley Sockets структуру, которая хранит
        //ip адрес и порт в понятном для Berkeley Sockets виде
        static sockaddr_in createAddress(intU32 l_address, unsigned short l_port);

        //метод возвращает специфическое значение INVALID_SOCKET,
        //позволяет быстро проверить уникальный идентификатор сокета в системе
        static SocketHandle invalidSocket();

        //закрывает сокет в системе
        static void close(SocketHandle l_socket);

        //устанавливает состояние сокета (блокирован или нет)
        static void setBlocking(SocketHandle l_socket, bool l_block);

        //возвращает последнюю зарегестрированную системой ошибку
        static Socket::Status getErrorStatus();
    };
}
}

#endif
