#ifndef NETWORK_TCPLISTENER_H
#define NETWORK_TCPLISTENER_H
#include "Export.hpp"
#include "Socket.hpp"
#include "IpAddress.hpp"

namespace wv{
    class TcpSocket;

    //класс, сокета типа Tcp, который ожидает подключение с определенного ip и порта
    class NETWORK_API TcpListener : public Socket {
    public:

        //конструктор
        TcpListener();

        //возвращает локальный порт сокета
        unsigned short getLocalPort() const;

        //сокет начинает слушать заданный порт и ip адресс,
        //ожидая входящего подключения
        Status Listen(unsigned short port,
                      const IpAddress& address = IpAddress::Any);

        //останавливает ожидание входящего подключения
        void Close();

        //в случае наличия входящего соединение,
        //метод предает параметры соединения сокету в аргументе
        //если слушающий сокет находится в блокирующем состоянии,
        //вызов этой функции заблокирует исполняемый поток до тех пор,
        //пока соединение не будет принято
        Status Accept(TcpSocket& socket);
    };

}
#endif // TCPSOCKET_H
