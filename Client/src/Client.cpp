#include "../include/Client.hpp"
#include "../include/Protocol.h"
#include <iomanip>

Client::Client(const Args& l_args) :
	m_args			(l_args),
	m_connected		(false),
	m_serverIp		(wv::IpAddress::LocalHost),
	m_protocol		(nullptr)
	{};

Client::~Client(){
	delete	m_protocol;
}

bool Client::Connect() {

	// извлечение типа подключения из аргументов,
	// указанных при запуске приложения
	ParseArgs();

	// создание инстанса класс @Protocol для управления сетью
	// типо протокола определён из желаемого протокола подключения
	if (m_protocolName == "udp") { m_protocol = new UDP(this); }
	else if (m_protocolName == "tcp") { m_protocol = new TCP(this); }

	// если @m_protocolName неподдерживаемый проток, вызывается исключение,
	// которое перехватывается в main()
	else throw ClientFails("Unsupported protocol \"" + m_protocolName + "\"");
	
	// попытка подключения к серверу по созданному протоколу
	return (m_protocol->Connect());
}

bool Client::Update(const std::string& l_send, std::string& l_receive) {
	// проверка @m_protocol на ненулевой указатель 
	if (!m_protocol) { return false; }

	// обработка строки @l_send, введеной пользователем,
	// и получения строки-ответа @l_receive от сервера
	return (m_protocol->Update(l_send, l_receive));
}
bool Client::Disconnect() {
	// если подключения нет, то ничего не делать
	if (!m_protocol) { return false; }

	// отключение от сервера
	return (m_protocol->Disconnect());
}

bool Client::IsConnected() const { return m_connected; }

void Client::ShowHelp() {
	std::cout << "Client application. List of arguments:\n";

	std::cout << std::endl;

	std::cout << std::setw(24) << std::right << "--protocol=xxx";
	std::cout << std::setw(4) << "";
	std::cout << "sets network protocol for use.\n";
	std::cout << std::setw(28) << "";
	std::cout << "Required. Option \"udp\" or \"tcp\".\n";

	std::cout << std::endl;

	/*std::cout << std::setw(24) << std::right << "--port=xxxx";
	std::cout << std::setw(4) << "";
	std::cout << "sets Server's port to connect to.\n";
	std::cout << std::setw(28) << "";
	std::cout << "Optional. Default: 5600 for tcp, 5800 for udp.\n";

	std::cout << std::endl;

	std::cout << std::setw(24) << std::right << "--ip=xxxx.xxxx.xxxx.xxxx";
	std::cout << std::setw(4) << "";
	std::cout << "sets Server's ip address to connect to.\n";
	std::cout << std::setw(28) << "";
	std::cout << "Optional. Default: localhost.\n";
	*/
}

void Client::ParseArgs() {
	// регулярное выражения для извлечения желаемого протокола
	m_protocolName = Parse(m_args[1], std::regex("(?:(?:--protocol=)|(?:-p=))([[:alpha:]]+)$"));
}

// если в строке @l_input содержится регулярное выражение @l_regular
// функция вернет первое совпадение
std::string Client::Parse(const std::string l_input, const std::regex l_regular) {
	std::smatch m;
	std::regex_search(l_input, m, l_regular);

	// возврат совпадения для первой захват-группы
	return m[1];
}