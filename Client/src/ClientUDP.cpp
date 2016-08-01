#include "../include/ClientUDP.hpp"
#include <iostream>
#include <vector>

ClientUDP::ClientUDP(const wv::IpAddress l_address) : Client(l_address) {}
ClientUDP::~ClientUDP(){ Disconnect(); }

bool ClientUDP::Connect() {
    if ((m_connected)||(m_serverIp == wv::IpAddress::None)) { return false; }
    m_socket.Bind(wv::Socket::AnyPort);
    std::cout << "UDP protocol" << std::endl
        <<"Bound client to port: " << m_socket.getLocalPort() << std::endl;
    m_connected = true;
    return true;
}

bool ClientUDP::Update(const std::string& l_send, std::string& l_reveive) {
    if (m_socket.Send(l_send.c_str(), l_send.size(), m_serverIp, ServerPortUDP) != wv::Socket::Done) {
        m_socket.Unbind();
        std::cout << "Failed to sent data\n";
        m_connected = false;
        return false;
    }
    l_reveive.clear();


    wv::IpAddress ip;
    PortNumber port;
    std::vector<char> buffer(wv::UdpSocket::MaxDatagramSize);
    std::size_t received = 0;

    wv::Socket::Status status =	m_socket.Receive(&buffer[0], buffer.size(), received, ip, port);
    if ((status == wv::Socket::Done) && (received > 0)) {
        l_reveive.append(&buffer[0], received);
        return true;
    }
    std::cout << "Failed to receive data\n";
    m_connected = false;
    return false;
}

void ClientUDP::Disconnect() {
    if (!m_connected) { return; }
    m_connected = false;
    m_socket.Unbind();
}
