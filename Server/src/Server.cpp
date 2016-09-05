#include "../include/Server.hpp"
#include <iostream>
#include <algorithm>

Server::Server() :
	m_running(false),
	m_stringHandler(nullptr)
	{}

Server::Server(void(*l_handler)(std::ostream&, const std::string&), std::ostream& cout) :
	m_running(false)
{
	//auto temp = std::bind(l_handler, cout, std::placeholders::_2);
	m_stringHandler = std::bind(l_handler, std::ref(cout), std::placeholders::_1);
}
Server::~Server() { Stop(); }

bool Server::Start() {
    if (m_running) { return false; }
    if (m_socketUDP.Bind(ServerPortUDP) != wv::Socket::Done) { return false; }
    m_socketUDP.SetBlocking(false);

    m_socketTCP.Listen(ServerPortTCP);
    m_socketTCP.SetBlocking(false);


    std::cout << "UDP port: " << m_socketUDP.getLocalPort() << std::endl;
    std::cout << "TCP port: " << ServerPortTCP << std::endl;
    m_running = true;
    std::cout << "Beginning to listen..." << std::endl;
    Setup();
    return true;
}

bool Server::Stop() {
    if (!m_running) { return false; }
    m_running = false;
    m_socketUDP.Unbind();
    m_socketTCP.Close();
    return true;
}

void Server::Update() {
    UpdateUDP();
    UpdateTCP();
}

void Server::Setup() {
    //m_running = false;
    m_totalReceived = 0;
}
bool Server::IsRunning() { return m_running; }

void Server::UpdateUDP() {
    wv::IpAddress ip;
    PortNumber port;
    std::vector<char> buffer(wv::UdpSocket::MaxDatagramSize);
    std::string string;
    std::size_t received = 0;

    wv::Socket::Status status =
        m_socketUDP.Receive(&buffer[0], buffer.size(), received, ip, port);
    if ((status == wv::Socket::Done) && (received > 0)) {
        m_totalReceived += received;
        string.clear();
        string.append(&buffer[0], received);
        buffer.clear();

        std::cout << "Ip " << ip << " port " << port << ": \"" << string << "\" -> "<< received << " bytes" << std::endl;
		if (m_stringHandler) {
			m_stringHandler(string);
		}
        std::cout << "Total received " << m_totalReceived << " bytes" << std::endl;

        wv::Socket::Status sendStatus = m_socketUDP.Send(string.c_str(), string.size(), ip, port);
        if (sendStatus == wv::Socket::Done) {
            std::cout << received << " bytes send back\n";
            std::cout << "------------------------------\n";
        }
    }    
}

void Server::UpdateTCP() {
    wv::TcpSocket client;
    if (m_socketTCP.Accept(client) == wv::Socket::Done)
    {
        std::cout << "New connection received from " << client.getRemoteAddress() << std::endl;
        //wv::IpAddress ip;
        //PortNumber port;
        std::vector<char> buffer(wv::UdpSocket::MaxDatagramSize);
        std::string string;
        std::size_t received = 0;

        wv::Socket::Status status =
            client.Receive(&buffer[0], buffer.size(), received);
        if ((status == wv::Socket::Done) && (received > 0)) {
            m_totalReceived += received;
            string.clear();
            string.append(&buffer[0], received);
            buffer.clear();

			std::cout << "Ip " << client.getRemoteAddress() << " port " << client.getRemotePort() << ": \"" << string << "\" -> " << received << " bytes" << std::endl;
			if (m_stringHandler) {
				m_stringHandler(string);
			}
            std::cout << "Total received " << m_totalReceived << " bytes" << std::endl;

            wv::Socket::Status sendStatus = client.Send(string.c_str(), string.size());
            if (sendStatus == wv::Socket::Done) {
                std::cout << received << " bytes send back\n";
                std::cout << "------------------------------\n";
                client.Disconnect();
                m_socketTCP.Listen(5600);
            }
        }
    }
}