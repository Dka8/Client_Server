#ifndef UDPSOCKET_H
#define UDPSOCKET_H
#include "Socket.h"
#include "IpAddress.h"


namespace wv {
	class UdpSocket : public Socket {
	public:
		//максимальный размер данных,
		//которые могуть быль отправлены за один раз через UDP сокет
		enum {
			MaxDatagramSize = 65507
		};

		//конструктор
		UdpSocket();

		//возвращает локальный порт сокета
		unsigned short getLocalPort() const;
		
		//привязывает сокет к определенному ip и порту
		//можно привязать сокет к любому свободному порту с помощью Socket::AnyPort
		//привязка необходима для передачи данных по сети
		Status Bind(unsigned short l_port, const IpAddress& l_address = IpAddress::Any);

		//отвязывает используемый порт
		void Unbind();

		//метод посылает данные по сети,
		//при попытке передать объем данных больше чем 65507 метод вернет ошибку
		//для передачи данных необходимо указать порт и ip принимающего сокета
		Status Send(const void* l_data, std::size_t l_size,
			const IpAddress& l_remoteAddress, unsigned short l_remotePort);

		//метод принимает данные
		//если сокет находится в блокирующем моде, вызов этого метода заблокирует
		//исполняемы поток до тех пор, пока данные не придут
		//метод позволяет получить ip адрес и порт сокета, который послал данные
		//и использовать их для ответа, например
		Status Receive(void *data, std::size_t l_size,
			std::size_t& l_received, IpAddress& remoteAddress, unsigned short& l_remotePort);

	private:

	};
}

#endif // UDPSOCKET_H
