#pragma once
#ifndef Client_H
#define Client_H
#include "Network.h"
#include "NetworkDefinition.h"
#include <iostream>
#include <string>
#include <vector>

//интерфейст для клиента
class Client
{
public:
	//клиенту необходимо знать ip адресс сервера
	Client(const wv::IpAddress l_address) :
		m_connected		(false),
		m_serverIp		(wv::IpAddress(l_address)) {};

	//вирутальный деструктор
	virtual ~Client() {};

	//вируальные методы, описывающие работу клиента
	//в зависимости от используемого протокола
	virtual bool Connect() = 0;
	virtual bool Update(const std::string& l_send, std::string& l_reveive) = 0;
	virtual void Disconnect() = 0;

	//проверка статуса клиента
	bool IsConnected() const { return m_connected; }
	
protected:
	
	//статус клиента
	bool			m_connected;

	//ip адресс сервера
	wv::IpAddress	m_serverIp;
};

#endif // !Client_H