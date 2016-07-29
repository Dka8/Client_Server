#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include "Socket.h"
#include "IpAddress.h"
#include <vector>

namespace wv{
    class TcpListener;

    class TcpSocket : public Socket{
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

	//класс, сокета типа Tcp, который ожидает подключение с определенного ip и порта
    class TcpListener : public Socket {
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
