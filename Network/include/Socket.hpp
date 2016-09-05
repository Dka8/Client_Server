#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H
#include "Export.hpp"
#include "SocketHandle.hpp"


namespace wv {

    class NETWORK_API Socket {
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
}

#endif // SOCKET_H
