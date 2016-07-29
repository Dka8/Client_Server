#pragma once
#ifndef ClientTCP_H
#define ClientTCP_H

#include "Client.h"

class ClientTCP : public Client
{
public:
	//�����������, �� ��������� ������ ������� �� "localhost"
	ClientTCP(const wv::IpAddress l_address = wv::IpAddress::LocalHost);
	~ClientTCP();

	//���������� ������ ������� ����������� � �������
	bool Connect();

	//������� � ��������, �������� ��������� ������������� ������,
	//� ��������� ������ �� �������
	bool Update(const std::string& l_send, std::string& l_reveive);

	//����� ��������� ������ �� �������,
	//� ��������� ������ ����������� ���������� �������
	void Disconnect();

private:

	//Tcp �����, ����� ������� ���������� ����� ����������� � ��������
	wv::TcpSocket		m_socket;
};

#endif // !ClientTCP_H