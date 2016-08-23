#include "../include/Client.hpp"
#include "../include/Protocol.h"

Client::Client(const wv::IpAddress l_address) :
	m_connected		(false),
	m_serverIp		(wv::IpAddress(l_address)),
	m_protocol		(nullptr)
	{};

Client::~Client(){
	delete	m_protocol;
}

bool Client::Connect() {
	if (!m_protocol) { return false; }
	return (m_protocol->Connect());
}
bool Client::Update(const std::string& l_send, std::string& l_receive) {
	if (!m_protocol) { return false; }
	return (m_protocol->Update(l_send, l_receive));
}
bool Client::Disconnect() {
	if (!m_protocol) { return false; }
	return (m_protocol->Disconnect());
}

bool Client::IsConnected() const { return m_connected; }
wv::IpAddress Client::GetServerIp() { return m_serverIp; }

void Client::SetProtocol(Protocol* l_protocol) {
	if (m_protocol) { delete m_protocol; }
	m_protocol = l_protocol;
}
void Client::Connected() { m_connected = true; }
void Client::Disconnected() { m_connected = false; }