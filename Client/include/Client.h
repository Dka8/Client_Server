#pragma once
#ifndef Client_H
#define Client_H
#include "Network.h"
#include "NetworkDefinition.h"
#include <iostream>
#include <string>
#include <vector>

//���������� ��� �������
class Client
{
public:
	//������� ���������� ����� ip ������ �������
	Client(const wv::IpAddress l_address) :
		m_connected		(false),
		m_serverIp		(wv::IpAddress(l_address)) {};

	//����������� ����������
	virtual ~Client() {};

	//���������� ������, ����������� ������ �������
	//� ����������� �� ������������� ���������
	virtual bool Connect() = 0;
	virtual bool Update(const std::string& l_send, std::string& l_reveive) = 0;
	virtual void Disconnect() = 0;

	//�������� ������� �������
	bool IsConnected() const { return m_connected; }
	
protected:
	
	//������ �������
	bool			m_connected;

	//ip ������ �������
	wv::IpAddress	m_serverIp;
};

#endif // !Client_H