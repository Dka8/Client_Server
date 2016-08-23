#ifndef SERVER_H
#define SERVER_H
#include "../../Network/Network.hpp"
#include "../../NetworkDefinition.hpp"
//#include <string>
#include <vector>
#include <thread>

class Server
{
public:
    Server();
    ~Server();

    //рабочий цикл сервера
    void Update();

    //запуск сервера
    bool Start();

    //остановка сервера
    bool Stop();

    //проверка статуса сервера
    bool IsRunning();

private:
    //настройка сервера и сокетов
    void Setup();

    //обработка информации, полученной через протокол Udp
    void UpdateUDP();

    //обработка информации, полученной через протокол Tcp
    void UpdateTCP();

    //обработка полученной строки
    //int digitSum(const std::string& l_string);
    //std::pair<int,int> digitMinMax(const std::string& l_string);
    //std::vector<int> digitSort(const std::string& l_string);

    //сокет для соединения по Udp
    wv::UdpSocket	m_socketUDP;

    //сокет для соединения по Tcp
    wv::TcpListener	m_socketTCP;

    //хранит информацию, запущен ли сервер
    bool m_running;

    //следит за колличеством полученных данных
    size_t	m_totalReceived;

	//std::thread m_udpThread;
};

#endif // !Server_H
