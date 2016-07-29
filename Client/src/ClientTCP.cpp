#include "ClientTCP.h"

ClientTCP::ClientTCP(const wv::IpAddress l_address) : Client(l_address) {}
ClientTCP::~ClientTCP() {}

bool ClientTCP::Connect() {
	if ((m_connected)||(m_serverIp == wv::IpAddress::None)) { return false; }
	//m_socket.Connect(m_serverIp, Network::ServerPortTCP);
	std::cout << "TCP protocol" << std::endl
		<< "Bound client to port: " << m_socket.getLocalPort() << std::endl;
	m_connected = true;
	return true;
}

bool ClientTCP::Update(const std::string& l_send, std::string& l_reveive) {
	m_socket.Connect(m_serverIp, ServerPortTCP);
	if (m_socket.Send(l_send.c_str(), l_send.size()) != wv::Socket::Done) {
		m_socket.Disconnect();
		std::cout << "Failed to sent data\n";
		m_connected = false;
		return false;
	}

	l_reveive.clear();
	std::vector<char> buffer(wv::UdpSocket::MaxDatagramSize);
	std::size_t received = 0;

	wv::Socket::Status status = m_socket.Receive(&buffer[0], buffer.size(), received);
	if ((status == wv::Socket::Done) && (received > 0)) {
		l_reveive.append(&buffer[0], received);
		m_socket.Disconnect();
		return true;
	}
	std::cout << "Failed to receive data\n";
	m_connected = false;
	return false;
}

void ClientTCP::Disconnect() {
	if (!m_connected) { return; }
	m_connected = false;
	m_socket.Disconnect();
}
