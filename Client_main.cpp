#include "Client\include\Client.hpp"
#include "Client\include\Protocol.h"
#include <string>
#include <unordered_set>
#include <iostream>

// аллиасы для хранения строк, для обращения к справке приложения
using HelpCommands = std::unordered_set<std::string>;

int main(int argc, char* argv[]) {
	// создаем вектор с аргументами командной строки
	Args	cmd;
	for (int i = 0; i < argc; ++i) {
		cmd.push_back(argv[i]);
	}

	// пробуем обратиться ко второму элементу в векторе
	try {
		std::string module;
		module = cmd.at(1);
	}
	// если второго аргумента не существует,
	// сообщаем об ошибке и прекращаем работу приложения
	catch (const std::out_of_range&) {
		std::cerr << "Error! Client application needs arguments. Use command --help for more info.\n";
		return 0;
	}
	
	// задаем аллиасы справки
	HelpCommands help({ "Help", "help", "--help", "-h" });

	// создаем инстанс класс клиент.
	Client client(cmd);

	// если второй аргумент командной строки соответствует одному из аллиасов справки,
	// показывает справку и прекращаем работу приложения
	auto itr = help.find(cmd[1]);
	if (itr != help.end()) {
		client.ShowHelp();
		return 0;
	}

	// пробуем запустить клиент с использованием протокола, полученного в аргументах
	try {
		client.Connect();
	}
	// в случае неудачи, сообщаем об этом пользователю и завершаем работу приложения
	catch (const ClientFails& reason) {
		std::cout << reason.what();
		std::cout << "Use \"-h\" for more info\n";
		return 0;
	}
    
	// проверяем, успешно ли подключение к серверу
    if (client.IsConnected()) {
		//в случае успеха, готовимся принимать строку от пользователя
        std::cout << "Input line to sent to server:\n";
        std::string lineToSend, lineToReceive;
        
		//принимаем строку от пользователя
		do {
			std::getline(std::cin, lineToSend);			
		} while (!lineToSend.size()); // проверка на пустую строку

        //отправляет строку на сервер,
        //и получаем ответ сервера
        if (client.Update(lineToSend, lineToReceive)) {
			std::cout << "> ";
			std::cout << lineToReceive << std::endl;
        }
		client.Disconnect();
    }
}
