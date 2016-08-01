#ifndef NETWORK_TCPSOCKET_H
#define NETWORK_TCPSOCKET_H
#include "Export.hpp"
#include "Socket.hpp"
#include "IpAddress.hpp"

namespace wv{
    class TcpListener;
    //class IpAddress;

    class NETWORK_API TcpSocket : public Socket{
    public:
        //конструктор по умолчанию
        TcpSocket();

        //возвращает порт, к которому локально привязат сокет
        unsigned short getLocalPort() const;

        //возвращает ip адресс, к которому сокет подключен удаленно
        IpAddress getRemoteAddress() const;

        //возвращает удаленный порт
        unsigned short getRemotePort() const;

        //подключение сокета к удаленному ip и порту
        //для успешного подключение необходимо получить ответ
        Status Connect(const IpAddress& remoteAddress,
            unsigned short remotePort);

        //закрывает соединение
        void Disconnect();

        //принимает данные, которые необходимо отправить,
        //при отправке данных идет отслеживание успешно посланного объема
        Status Send(const void* data, std::size_t size);

        //отправляет данные на подключенный сокет,
        Status Send(const void* data, std::size_t size, std::size_t& sent);

        //принимает данные от подключенного сокета,
        //определяет размер полученных данных
        Status Receive(void* data, std::size_t size, std::size_t& received);

    private:
        friend class TcpListener;
    };
}
#endif // TCPSOCKET_H
