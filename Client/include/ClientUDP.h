#pragma once
#ifndef Client_UDP
#define Client_UDP
#include "Client.h"

class ClientUDP : public Client
{
public:

	//�����������, �� ��������� ������ ������� �� "localhost"
	ClientUDP(const wv::IpAddress l_address = wv::IpAddress::LocalHost);
	~ClientUDP();

	//���������� ������ ������� ����������� � �������
	bool Connect();

	//������� � ��������, �������� ��������� ������������� ������,
	//� ��������� ������ �� �������
	bool Update(const std::string& l_send, std::string& l_reveive);
	
	//����� ��������� ������ �� �������,
	//� ��������� ������ ����������� ���������� �������
	void Disconnect();

private:
	
	//Udp �����, ����� ������� ���������� ����� ����������� � ��������
	wv::UdpSocket		m_socket;
};

#endif // !Client_UDP