#pragma once
#ifndef ClientTCP_H
#define ClientTCP_H

#include "Client.h"

class ClientTCP : public Client
{
public:
	//конструктор, по умолчанию сервер запущен на "localhost"
	ClientTCP(const wv::IpAddress l_address = wv::IpAddress::LocalHost);
	~ClientTCP();

	//возвращает статус попытки подключения к серверу
	bool Connect();

	//общение с сервером, отправка введенных пользователем данных,
	//и получение ответа от сервера
	bool Update(const std::string& l_send, std::string& l_reveive);

	//метод отключает клиент от сервера,
	//и завершает работу консольного приложения клиента
	void Disconnect();

private:

	//Tcp сокет, через который происходит обмен информацией с сервером
	wv::TcpSocket		m_socket;
};

#endif // !ClientTCP_H