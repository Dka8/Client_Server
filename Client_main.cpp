//#include "Network.h"
#include "ClientUDP.h"
#include "ClientTCP.h"
#include <sstream>

int main() {
	//������� ������ ��������� �� ������ ������
	Client*		client(NULL);

	//������������� �����
	std::cout << "Welcom!" << std::endl;
	std::cout << "Input connect protocol and Ip server's address" << std::endl;
	std::cout << "TCP / Tcp / tcp or UDP / Udp / udp" << std::endl;
	std::cout << "Ip adress example: 127.0.0.1" <<std::endl;

	//���������� ��� �������� ��������� ������
	std::string input, protocol;
	wv::IpAddress address;

	//���� ���� �� ������� �������� ������ �� ������������
	while (true) {

		//������� �������� ������������� ������
		std::getline(std::cin, input);
		std::stringstream line(input);

		//�������� ������ �������� ������������
		if (line >> protocol) {
			if (protocol == "exit") {
				return 0;
			}
			if (((protocol == "UDP")
				|| (protocol == "Udp")
				|| (protocol == "udp"))
					|| ((protocol == "TCP")
					|| (protocol == "Tcp")
					|| (protocol == "tcp"))) {
				std::string address_str;

				//��������� ���� �� ������ �������� ip �������,
				//���� ��� �� ������������ ����� � "localhost"
				if ((line >> address_str) && (wv::IpAddress(address_str) != wv::IpAddress::None)) {
					address = wv::IpAddress(address_str);
				}
				else {
					address = wv::IpAddress::LocalHost;
					break;
				}	
			}
			else {
				std::cout << "Wrong protocol try again or print \"exit\"\n";
				continue;
			}			
		}
	}
	
	//� ����������� �� ���������� ������������� ��������� �����������,
	//������� ��������������� ������� ������� ���� Client
	if ((protocol == "UDP") || (protocol == "Udp") || (protocol == "udp")) {
		std::cout << "Setting your client to use UDP protocol\n";
		client = new ClientUDP(address);
	}
	else if ((protocol == "TCP") || (protocol == "Tcp") || (protocol == "tcp")) {
		std::cout << "Setting your client to use TCP protocol\n";
		client = new ClientTCP(address);
	}

	//��������� ���������� ��������� ���� �� ������ �������
	else {
		return 1;
	}

	//�������� ������������ � �������
	if (client->Connect()) {

		//� ������ ������, ��������� ��������� ������ �� ������������
		std::cout << "Input line to sent to server or print \"exit\":\n";
		while (client->IsConnected()) {

			//��������� ������ �� ������������
			std::string lineToSend, lineToReceive;
			std::getline(std::cin, lineToSend);

			//�������� �� ������ ������
			if (!lineToSend.size()) { continue; }

			//����� �� ����� ��� ��������� ����� exit
			if (lineToSend == "exit") { client->Disconnect(); }

			//���������� ������ �� ������,
			//� �������� ������ ����� �������
			if (client->Update(lineToSend, lineToReceive)) {
				std::cout << "> ";
				std::cout << lineToReceive << std::endl << std::endl;
			}
		}
	}

	//��� ������ �� ����� ����������� ������ ������� �������� ���� Client
	//� ��������� ���������� ���������
	delete client;
	client = NULL;
}
