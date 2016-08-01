#include "../include/Server.hpp"
#include <iostream>
#include <algorithm>

Server::Server() : m_running(false){}
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

        //ñ÷èòàåì êîëëè÷åñòâî öèôð â ñòðîêå
        int sum = digitSum(string);
        //ìèíèìàëüíûé è ìàêñèìàëüíûé ýëåìåíòû
        std::pair<int,int> p = digitMinMax(string);
        std::vector<int> s = digitSort(string);
        if (s.size()) {
            std::cout << "Sum = " << sum << std::endl;
            std::cout << "Min = " << p.second << " Max = " << p.first << std::endl;
            std::cout << "Sort: ";
            for (std::vector<int>::const_iterator itr = s.begin(); itr != s.end(); ++itr) {
                std::cout << *itr << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Ip " << ip << " port " << port << ": \"" << string << "\" -> "<< received << " bytes" << std::endl;
        //std::cout << "Total received " << m_totalReceived << " bytes" << std::endl;

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
            //ñ÷èòàåì êîëëè÷åñòâî öèôð â ñòðîêå
            int sum = digitSum(string);
            //ìèíèìàëüíûé è ìàêñèìàëüíûé ýëåìåíòû
            std::pair<int, int> p = digitMinMax(string);
            //ñîðòèðîâêà ïî óáûâàíèþ
            std::vector<int> s = digitSort(string);
            if (s.size()) {
                std::cout << "Sum = " << sum << std::endl;
                std::cout << "Min = " << p.second << " Max = " << p.first << std::endl;
                std::cout << "Sort: ";
                for (std::vector<int>::const_iterator itr = s.begin(); itr != s.end(); ++itr) {
                    std::cout << *itr << " ";
                }
                std::cout << std::endl;
            }

            std::cout << "Ip " << client.getRemoteAddress() << " port " << client.getRemotePort() << ": \"" << string << "\" -> " << received << " bytes" << std::endl;
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

struct Sum {
    Sum() { sum = 0; }
    void operator()(int n) { sum += n; }

    int sum;
};

int Server::digitSum(const std::string& l_string) {
    std::vector<unsigned int> digit;
    for (std::string::const_iterator itr = l_string.begin(); itr != l_string.end(); ++itr) {
        if ((*itr >= '0') && (*itr <= '9'))//Åñëè ÷èñëî
            digit.push_back(*itr - '0');
    }
    if (digit.size()) {
        Sum s = std::for_each(digit.begin(), digit.end(), Sum());
        return s.sum;
    }
    return 0;
}

struct Comp {
    Comp(){}
    bool operator()(const int& a, const int& b) {
        return a > b;
    }
};

std::pair<int, int> Server::digitMinMax(const std::string& l_string) {
    std::vector<int> digit;
    for (std::string::const_iterator itr = l_string.begin(); itr != l_string.end(); ++itr) {
        if ((*itr >= '0') && (*itr <= '9'))//Åñëè ÷èñëî
            digit.push_back(*itr - '0');
    }
    if (digit.size()) {
        return std::make_pair(*std::min_element(digit.begin(), digit.end(), Comp()),
            *std::max_element(digit.begin(), digit.end(), Comp()));
    }
    else {
        return std::make_pair(0, 0);
    }
}

std::vector<int> Server::digitSort(const std::string& l_string) {
    std::vector<int> digit;
    for (std::string::const_iterator itr = l_string.begin(); itr != l_string.end(); ++itr) {
        if ((*itr >= '0') && (*itr <= '9'))//Åñëè ÷èñëî
            digit.push_back(*itr - '0');
    }
    if (digit.size()) {
        std::sort(digit.begin(), digit.end(), Comp());
        return digit;
    }
    digit.clear();
    return digit;
}
