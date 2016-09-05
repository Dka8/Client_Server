#ifndef CLIENT_H
#define CLIENT_H
#include "../../Network/Network.hpp"
#include "../../NetworkDefinition.hpp"
#include <vector>
#include <regex>
#include <string>

// вектор для хранения аргументов командной строки
using Args = std::vector<std::string>;

// структору для рабуты с исключениями клиента
struct ClientFails
{
	ClientFails() : m_reason("") {};
	ClientFails(const std::string& l_reason) : m_reason(l_reason) {};
	std::string what() const {
		return ("Client fails! " + m_reason + "\n");
	}
	std::string		m_reason;
};

// класс описывает интерфейс работы с протоколами
// реализация осуществена на основе паттерна "стратегия"
class Protocol;

// 
class Client
{
public:
    // explicit потому, что принимает один аргумент
	explicit Client(const Args&);

	// удаляем конструктор копирования
	Client(const Client&) = delete;

	// удаляем конструктор перемещения
	Client(Client&&) = delete;

	// удаляем оператор присваивания
	Client& operator = (const Client&) = delete;

	// удаляем оператор перемещения
	Client& operator = (Client&&) = delete;

    // деструктор
	~Client();

    // основные методы для работы с клиентом
	// попытка подключиться к серверу
    bool Connect();
	
	// отправка строки и ожидание ответа от сервера
    bool Update(const std::string& l_send, std::string& l_reveive);
	
	// отключение от сервера
    bool Disconnect();

    // проверка статуса клиента
	bool IsConnected() const;
	
	// краткая справка
	void ShowHelp();
private:
	// даем классу доступ к privat членам для их изменения и управления подключением 
	friend Protocol;

	// функция для извлечения с помощью регулярного выражения
	// желаемого типа подключения из аргументов,
	// указанных при запуске приложения
	void ParseArgs();

	// работа с одним агрументов
	static std::string Parse(const std::string, const std::regex);

	// вектор с аргументами, указанными при запуске приложения
	Args				m_args;

	// имя протокола (например "udp")
	std::string			m_protocolName;
	
	// указатель на класс, который работает с сетью,
	// на основании указанного протокола
	Protocol*			m_protocol;
    
	//статус клиента
    bool				m_connected;

    //ip адресс сервера
    wv::IpAddress		m_serverIp;
};

#endif // !Client_H
