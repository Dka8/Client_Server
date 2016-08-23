#ifndef WAVE_PROTOCOL_H
#define WAVE_PROTOCOL_H
#include "../../Network/Network.hpp"
#include "../../NetworkDefinition.hpp"
#include "Client.hpp"
#include <iostream>
#include <vector>

class Protocol {
public:
	Protocol(Client* l_client) :
		m_client	(l_client)
	{}
	virtual ~Protocol() {};

	virtual bool Connect() = 0;
	virtual bool Update(const std::string& l_send, std::string& l_reseive) = 0;
	virtual bool Disconnect() = 0;
protected:
	Client*		m_client;
};

#endif // !WAVE_PROTOCOL_H

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
		m_client->Connected();
		return true;
	}
	bool Update(const std::string& l_send, std::string& l_receive) {
		if (m_socket.Send(l_send.c_str(), l_send.size(), m_client->GetServerIp(), ServerPortUDP) != wv::Socket::Done) {
			m_socket.Unbind();
			std::cout << "Failed to sent data\n";
			m_client->Disconnected();
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
		m_client->Disconnected();
		return false;
	}
	bool Disconnect() {
		if (!m_client->IsConnected()) { return false; }
		m_client->Disconnected();
		m_socket.Unbind();
		return true;
	}
private:
	wv::UdpSocket		m_socket;
};

class TCP : public Protocol {
public:
	TCP(Client* l_client) :
		Protocol(l_client)
	{};
	~TCP() {};

	bool Connect() {
		if (m_client->IsConnected()) { return false; }
		//m_socket.Connect(m_serverIp, Network::ServerPortTCP);
		std::cout << "TCP protocol" << std::endl
			<< "Bound client to port: " << m_socket.getLocalPort() << std::endl;
		m_client->Connected();
		return true;
	}
	bool Update(const std::string& l_send, std::string& l_receive) {
		m_socket.Connect(m_client->GetServerIp(), ServerPortTCP);
		if (m_socket.Send(l_send.c_str(), l_send.size()) != wv::Socket::Done) {
			m_socket.Disconnect();
			std::cout << "Failed to sent data\n";
			m_client->Disconnected();
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
		m_client->Disconnected();
		return false;
	}
	bool Disconnect() {
		if (!m_client->IsConnected()) { return false; }
		m_socket.Disconnect();
		m_client->Disconnected();
		return true;
	}
private:
	wv::TcpSocket		m_socket;
};