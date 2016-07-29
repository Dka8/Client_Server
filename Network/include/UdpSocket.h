#ifndef UDPSOCKET_H
#define UDPSOCKET_H
#include "Socket.h"
#include "IpAddress.h"


namespace wv {
	class UdpSocket : public Socket {
	public:
		//������������ ������ ������,
		//������� ������ ���� ���������� �� ���� ��� ����� UDP �����
		enum {
			MaxDatagramSize = 65507
		};

		//�����������
		UdpSocket();

		//���������� ��������� ���� ������
		unsigned short getLocalPort() const;
		
		//����������� ����� � ������������� ip � �����
		//����� ��������� ����� � ������ ���������� ����� � ������� Socket::AnyPort
		//�������� ���������� ��� �������� ������ �� ����
		Status Bind(unsigned short l_port, const IpAddress& l_address = IpAddress::Any);

		//���������� ������������ ����
		void Unbind();

		//����� �������� ������ �� ����,
		//��� ������� �������� ����� ������ ������ ��� 65507 ����� ������ ������
		//��� �������� ������ ���������� ������� ���� � ip ������������ ������
		Status Send(const void* l_data, std::size_t l_size,
			const IpAddress& l_remoteAddress, unsigned short l_remotePort);

		//����� ��������� ������
		//���� ����� ��������� � ����������� ����, ����� ����� ������ �����������
		//���������� ����� �� ��� ���, ���� ������ �� ������
		//����� ��������� �������� ip ����� � ���� ������, ������� ������ ������
		//� ������������ �� ��� ������, ��������
		Status Receive(void *data, std::size_t l_size,
			std::size_t& l_received, IpAddress& remoteAddress, unsigned short& l_remotePort);

	private:

	};
}

#endif // UDPSOCKET_H
