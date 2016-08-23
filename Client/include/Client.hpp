#ifndef CLIENT_H
#define CLIENT_H
#include "../../Network/Network.hpp"
#include "../../NetworkDefinition.hpp"

class Protocol;
//интерфейс для клиента
class Client
{
public:
    //клиенту необходимо знать ip адресс сервера
	Client(const wv::IpAddress l_address);

    //вирутальный деструктор
	~Client();

    //вируальные методы, описывающие работу клиента
    //в зависимости от используемого протокола
    bool Connect();
    bool Update(const std::string& l_send, std::string& l_reveive);
    bool Disconnect();

    //проверка статуса клиента
	bool IsConnected() const;
	wv::IpAddress GetServerIp();

	void SetProtocol(Protocol* l_protocol);
	void Connected();
	void Disconnected();

private:

	Protocol*		m_protocol;
    //статус клиента
    bool			m_connected;

    //ip адресс сервера
    wv::IpAddress	m_serverIp;
};

#endif // !Client_H
