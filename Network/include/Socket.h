#ifndef SOCKET_H
#define SOCKET_H
#include "Config.h"
#include "SafeTypes.h"
#include "SocketHandle.h"

//���������� ������������� ��� ������� �������� �������� � ���������� Berkeley Sockets
#include <winsock2.h>
#include <ws2tcpip.h>


namespace wv {

	class Socket {
	public:

		//��������� ������ ����� ������� �������������� � ���
		enum Status {
			Done,			//����� ������� ������ ��� �������� ������
			NotReady,		//����� �� ����� ��������� ��� ���������� ������
			Partial,		//������� ��������� ���� ���� ������
			Disconnected,	//TCP ����� ��� ����������
			Error			//��������� ������
		};
		enum {
			AnyPort = 0		//��������� ������� ������� ����� ��������� ���� ��� ������
		};
		virtual ~Socket();

		//thue - ������������� blocking mode
		//false - ������������� non-blocking mode
		//���� ����� ��������� � ����������� ���������, �� ��� ������ ������,
		//������� ��������� ������, ���������� ���������� ��������� ��� �����
		void SetBlocking(bool l_blocking);

		//�������� ������ � ����� ��������� ��������� �����
		bool isBlocking() const;
		
	protected:
		//���������� ���� ������,
		//�������� ������������ ���������� ��� ������ ������������ ������
		enum Type {
			Tcp, Udp
		};

		//����������� ������, ��������� ��� ������ ��� ��������
		Socket(Type type);

		// ���������� ���������� ������������� ������ � �������
		SocketHandle GetHandle() const;

		//������� � ������������ ����� � �������
		void Create();

		//����������� ��������� ��������� ������ � �������
		//UDP �������� ����������� BROADCAST
		//TCP ��������� �������� ������
		void Create(SocketHandle l_handle);

		//��������� �����
		void Close();

	private:
		Type			m_type;			// ������ ��� ������ (UDP ��� TCP)
		SocketHandle	m_socket;		// ���������� ������������� ������ � �������
		bool			m_isBlocking;	// ������ ���������� � � ����� ��������� ��������� �����
	};

	namespace be {

		//��������������� ����� ��� ������ �������� � Berkeley Sockets
		//��� ������ � ������ ������ ����������������
		class SocketBE {
		public:
			typedef int AddrLength;

			//���������� ������������� Berkeley Sockets ���������, ������� ������
			//ip ����� � ���� � �������� ��� Berkeley Sockets ����
			static sockaddr_in createAddress(intU32 l_address, intU16 l_port);
			
			//����� ���������� ������������� �������� INVALID_SOCKET,
			//��������� ������ ��������� ���������� ������������� ������ � �������
			static SocketHandle invalidSocket();

			//��������� ����� � �������
			static void close(SocketHandle l_socket);

			//������������� ��������� ������ (���������� ��� ���)
			static void setBlocking(SocketHandle l_socket, bool l_block);

			//���������� ��������� ������������������ �������� ������
			static Socket::Status getErrorStatus();
		};
	}
}

#endif // SOCKET_H
