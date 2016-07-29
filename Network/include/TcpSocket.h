#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include "Socket.h"
#include "IpAddress.h"
#include <vector>

namespace wv{
    class TcpListener;

    class TcpSocket : public Socket{
    public:
		//����������� �� ���������
        TcpSocket();

		//���������� ����, � �������� �������� �������� �����
        unsigned short getLocalPort() const;

		//���������� ip ������, � �������� ����� ��������� ��������
        IpAddress getRemoteAddress() const;

		//���������� ��������� ����
        unsigned short getRemotePort() const;

		//����������� ������ � ���������� ip � �����
		//��� ��������� ����������� ���������� �������� �����
        Status Connect(const IpAddress& remoteAddress,
            unsigned short remotePort);

		//��������� ����������
        void Disconnect();

		//��������� ������, ������� ���������� ���������,
		//��� �������� ������ ���� ������������ ������� ���������� ������
        Status Send(const void* data, std::size_t size);

		//���������� ������ �� ������������ �����,
        Status Send(const void* data, std::size_t size, std::size_t& sent);

		//��������� ������ �� ������������� ������,
		//���������� ������ ���������� ������
        Status Receive(void* data, std::size_t size, std::size_t& received);

    private:
		friend class TcpListener;
    };

	//�����, ������ ���� Tcp, ������� ������� ����������� � ������������� ip � �����
    class TcpListener : public Socket {
    public:

		//�����������
        TcpListener();

		//���������� ��������� ���� ������
        unsigned short getLocalPort() const;

		//����� �������� ������� �������� ���� � ip ������,
		//������ ��������� �����������
        Status Listen(unsigned short port,
                      const IpAddress& address = IpAddress::Any);
        
		//������������� �������� ��������� �����������
		void Close();

		//� ������ ������� ��������� ����������,
		//����� ������� ��������� ���������� ������ � ���������
		//���� ��������� ����� ��������� � ����������� ���������,
		//����� ���� ������� ����������� ����������� ����� �� ��� ���,
		//���� ���������� �� ����� �������
        Status Accept(TcpSocket& socket);
    };

}
#endif // TCPSOCKET_H
