#ifndef SOCKET_H
#define SOCKET_H
#include "Config.h"
#include "SafeTypes.h"
#include "SocketHandle.h"

//библиотеки специфические для виндоус содержат описание и исполнение Berkeley Sockets
#include <winsock2.h>
#include <ws2tcpip.h>


namespace wv {

	class Socket {
	public:

		//состояние сокета после попытки взаимодействия с ним
		enum Status {
			Done,			//сокет успешно принял или отправил данные
			NotReady,		//сокет не готов принимать или отправлять данные
			Partial,		//удалось отправить лишь чать данных
			Disconnected,	//TCP сокет был отсоединен
			Error			//произошла ошибка
		};
		enum {
			AnyPort = 0		//позволяет системе выбрать любой доступный порт для сокета
		};
		virtual ~Socket();

		//thue - соответствует blocking mode
		//false - соответствует non-blocking mode
		//если сокет находится в блокирующем состоянии, то при вызове метода,
		//который принимает данные, произойдет блокировка программы или ветви
		void SetBlocking(bool l_blocking);

		//позвляет узнать в каком состоянии находится сокет
		bool isBlocking() const;

	protected:
		//определяет типо сокета,
		//является обязательным параметром при вызове конструктора класса
		enum Type {
			Tcp, Udp
		};

		//конструктор класса, принимает тип сокета как параметр
		Socket(Type type);

		// возвращает уникальный идентификатор сокета в системе
		SocketHandle GetHandle() const;

		//сознает и регестрирует сокет в системе
		void Create();

		//настраивает некоторые параметра сокета в системе
		//UDP включает возможность BROADCAST
		//TCP отключает Алгоритм Нейгла
		void Create(SocketHandle l_handle);

		//закрывает сокет
		void Close();

	private:
		Type			m_type;			// хранит тип сокета (UDP или TCP)
		SocketHandle	m_socket;		// уникальный идентификатор сокета в системе
		bool			m_isBlocking;	// хранит информацию о в каком состоянии находится сокет
	};


	namespace be {

		//вспомогательный класс для работы напрямую с Berkeley Sockets
		//все медоты в данном классе сокетонезависимы
		class SocketBE {
		public:
			typedef int AddrLength;

			//возвращает специфическую Berkeley Sockets структуру, которая хранит
			//ip адрес и порт в понятном для Berkeley Sockets виде
			static sockaddr_in createAddress(intU32 l_address, intU16 l_port);

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

#endif // SOCKET_H
