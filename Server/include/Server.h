#pragma once
#ifndef Server_H
#define Server_H
#include "Network.h"
#include "NetworkDefinition.h"
#include <string>
#include <iostream>
#include <vector>

class Server
{
public:
	Server();
	~Server();

	//������� ���� �������
	void Update();

	//������ �������
	bool Start();

	//��������� �������
	bool Stop();

	//�������� ������� �������
	bool IsRunning();

private:
	//��������� ������� � �������
	void Setup();

	//��������� ����������, ���������� ����� �������� Udp
	void UpdateUDP();

	//��������� ����������, ���������� ����� �������� Tcp
	void UpdateTCP();

	//��������� ���������� ������
	int digitSum(const std::string& l_string);
	std::pair<int,int> digitMinMax(const std::string& l_string);
	std::vector<int> digitSort(const std::string& l_string);

	//����� ��� ���������� �� Udp
	wv::UdpSocket	m_socketUDP;

	//����� ��� ���������� �� Tcp
	wv::TcpListener	m_socketTCP;
	
	//������ ����������, ������� �� ������
	bool m_running;

	//������ �� ������������ ���������� ������
	size_t	m_totalReceived;
};




#endif // !Server_H