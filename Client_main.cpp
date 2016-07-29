//#include "Network.h"
#include "ClientUDP.h"
#include "ClientTCP.h"
#include <sstream>

int main() {
	//создаем пустой указатель на объект клиент
	Client*		client(NULL);

	//вступительные слова
	std::cout << "Welcom!" << std::endl;
	std::cout << "Input connect protocol and Ip server's address" << std::endl;
	std::cout << "TCP / Tcp / tcp or UDP / Udp / udp" << std::endl;
	std::cout << "Ip adress example: 127.0.0.1" <<std::endl;

	//переменные для хранения введенных данных
	std::string input, protocol;
	wv::IpAddress address;

	//цикл пока не получим значимые данные от пользователя
	while (true) {

		//стримим введеную пользователем строку
		std::getline(std::cin, input);
		std::stringstream line(input);

		//получаем первый параметр пользователя
		if (line >> protocol) {
			if (protocol == "exit") {
				return 0;
			}
			if (((protocol == "UDP")
				|| (protocol == "Udp")
				|| (protocol == "udp"))
					|| ((protocol == "TCP")
					|| (protocol == "Tcp")
					|| (protocol == "tcp"))) {
				std::string address_str;

				//проверяем если ли второй параметр ip сервера,
				//если нет то подключаться будем к "localhost"
				if ((line >> address_str) && (wv::IpAddress(address_str) != wv::IpAddress::None)) {
					address = wv::IpAddress(address_str);
				}
				else {
					address = wv::IpAddress::LocalHost;
					break;
				}	
			}
			else {
				std::cout << "Wrong protocol try again or print \"exit\"\n";
				continue;
			}			
		}
	}
	
	//в зависимости от введенного пользователем протокола подключения,
	//создаем соответствующий инстанс объекта типа Client
	if ((protocol == "UDP") || (protocol == "Udp") || (protocol == "udp")) {
		std::cout << "Setting your client to use UDP protocol\n";
		client = new ClientUDP(address);
	}
	else if ((protocol == "TCP") || (protocol == "Tcp") || (protocol == "tcp")) {
		std::cout << "Setting your client to use TCP protocol\n";
		client = new ClientTCP(address);
	}

	//благадаря предыдущим проверкам сюда не должны попасть
	else {
		return 1;
	}

	//пытаемся подключиться к серверу
	if (client->Connect()) {

		//в случае успеха, готовимся принимать строку от пользователя
		std::cout << "Input line to sent to server or print \"exit\":\n";
		while (client->IsConnected()) {

			//принимаем строку от пользователя
			std::string lineToSend, lineToReceive;
			std::getline(std::cin, lineToSend);

			//проверка на пустую строку
			if (!lineToSend.size()) { continue; }

			//выход из цикла при написании слова exit
			if (lineToSend == "exit") { client->Disconnect(); }

			//отправляет строку на сервер,
			//и получаем ссылке ответ сервера
			if (client->Update(lineToSend, lineToReceive)) {
				std::cout << "> ";
				std::cout << lineToReceive << std::endl << std::endl;
			}
		}
	}

	//при выходе из цикла освобождаем память занятую объектом типа Client
	//и завершаем выполнение программы
	delete client;
	client = NULL;
}
