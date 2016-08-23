#include "Server/include/Server.hpp"
#include <iostream>

void CommandProcess(Server* l_server) {
	while (l_server->IsRunning()) {
		std::string str;
		std::getline(std::cin, str);
		if (str == "!quit") {
			l_server->Stop();
			break;
		}
	}
}

int main() {

    //создаем инстанс объекта сервер
    Server server;


    //пытаемся запустить сервер
    std::cout << "Starting server...\n";
	if (server.Start()) {
		std::thread c(CommandProcess, &server);
		c.detach();

		while (server.IsRunning()) {
			server.Update();
		}
	}
    

    //в случае успешного запуска
    //входим в основной рабочий цикл сервера
    

    std::cout << "Server has been stoped\n";
    return 0;
}
