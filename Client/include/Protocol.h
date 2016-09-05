#ifndef WAVE_PROTOCOL_H
#define WAVE_PROTOCOL_H
#include "../../Network/Network.hpp"
#include "../../NetworkDefinition.hpp"
#include "Client.hpp"
#include <iostream>
#include <vector>


// класс интерфейс, определяет общие методы работы с протоколами
// родительский класс для каждого конкретного протокола
// логика работы основана на паттерне "стратегия"
// хранит указатель на инстанс класса @Client
class Protocol {
public:
	Protocol(Client* l_client) :
		m_client	(l_client)
	{}
	virtual ~Protocol() {};

	// подключает клиент к серверу
	virtual bool Connect() = 0;

	// отправляет на сервер и принимает строку ответа от сервера
	virtual bool Update(const std::string& l_send, std::string& l_reseive) = 0;

	// отключает клиент от сервера
	virtual bool Disconnect() = 0;
protected:
	// изменяет переменную, отвечающую за статус подключения в классе @Client
	void Connected() { m_client->m_connected = true; }
	void Disconnected() { m_client->m_connected = false; }
	wv::IpAddress GetServerIp() { return m_client->m_serverIp; }

	// указатель на инстанс @Client
	Client*		m_client;
};

// логика работы с сетью по протоколу Udp
class UDP : public Protocol {
public:
	UDP(Client* l_client) :
		Protocol(l_client)
	{};
	~UDP() {};

	bool Connect() {
		if (m_client->IsConnected()) { return false; }
		m_socket.Bind(wv::Socket::AnyPort);
		std::cout << "UDP protocol" << std::endl
			<< "Bound client to port: " << m_socket.getLocalPort() << std::endl;
		Connected();
		return true;
	}
	bool Update(const std::string& l_send, std::string& l_receive) {
		if (m_socket.Send(l_send.c_str(), l_send.size(), GetServerIp(), ServerPortUDP) != wv::Socket::Done) {
			m_socket.Unbind();
			std::cout << "Failed to sent data\n";
			Disconnected();
			return false;
		}

		l_receive.clear();
		wv::IpAddress ip;
		PortNumber port;
		std::vector<char> buffer(wv::UdpSocket::MaxDatagramSize);
		std::size_t received = 0;

		wv::Socket::Status status = m_socket.Receive(&buffer[0], buffer.size(), received, ip, port);
		if ((status == wv::Socket::Done) && (received > 0)) {
			l_receive.append(&buffer[0], received);
			return true;
		}
		std::cout << "Failed to receive data\n";
		Disconnected();
		return false;
	}
	bool Disconnect() {
		if (!m_client->IsConnected()) { return false; }
		Disconnected();
		m_socket.Unbind();
		return true;
	}
private:
	wv::UdpSocket		m_socket;
};

// логика работы с сетью по протоколу Tcp
class TCP : public Protocol {
public:
	TCP(Client* l_client) :
		Protocol(l_client)
	{};
	~TCP() {};

	bool Connect() {
		if (m_client->IsConnected()) { return false; }
		std::cout << "TCP protocol" << std::endl
			<< "Bound client to port: " << m_socket.getLocalPort() << std::endl;
		Connected();
		return true;
	}
	bool Update(const std::string& l_send, std::string& l_receive) {
		m_socket.Connect(GetServerIp(), ServerPortTCP);
		if (m_socket.Send(l_send.c_str(), l_send.size()) != wv::Socket::Done) {
			m_socket.Disconnect();
			std::cout << "Failed to sent data\n";
			Disconnected();
			return false;
		}

		l_receive.clear();
		std::vector<char> buffer(wv::UdpSocket::MaxDatagramSize);
		std::size_t received = 0;

		wv::Socket::Status status = m_socket.Receive(&buffer[0], buffer.size(), received);
		if ((status == wv::Socket::Done) && (received > 0)) {
			l_receive.append(&buffer[0], received);
			m_socket.Disconnect();
			return true;
		}
		std::cout << "Failed to receive data\n";
		Disconnected();
		return false;
	}
	bool Disconnect() {
		if (!m_client->IsConnected()) { return false; }
		m_socket.Disconnect();
		Disconnected();
		return true;
	}
private:
	wv::TcpSocket		m_socket;
};

#endif // !WAVE_PROTOCOL_H