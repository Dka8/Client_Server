#pragma once
#ifndef Client_UDP
#define Client_UDP
#include "Client.h"

class ClientUDP : public Client
{
public:

	//конструктор, по умолчанию сервер запущен на "localhost"
	ClientUDP(const wv::IpAddress l_address = wv::IpAddress::LocalHost);
	~ClientUDP();

	//возвращает статус попытки подключения к серверу
	bool Connect();

	//общение с сервером, отправка введенных пользователем данных,
	//и получение ответа от сервера
	bool Update(const std::string& l_send, std::string& l_reveive);
	
	//метод отключает клиент от сервера,
	//и завершает работу консольного приложения клиента
	void Disconnect();

private:
	
	//Udp сокет, через который происходит обмен информацией с сервером
	wv::UdpSocket		m_socket;
};

#endif // !Client_UDP