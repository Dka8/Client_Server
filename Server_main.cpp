#include "Server/include/Server.hpp"
#include <iostream>
#include <thread>
#include <regex>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

// функция для обработки входящих на сервер данных
void StringHandler(std::ostream& cout, const std::string& l_string) {
	
	// создаем вектор, для хранения всех цифр,
	// найденных во входящей строке
	std::vector<int> digits;

	// регулярное выражение, для поиска цифр
	std::regex regularExp("[[:digit:]]");
	const std::sregex_token_iterator end;

	// помещаем все вхождения цифры в вектор @digits
	for (std::sregex_token_iterator itr(l_string.begin(), l_string.end(), regularExp, 0); itr != end; ++itr) {
		std::string d = *itr;
		digits.push_back(atoi(d.c_str()));
	}
	
	// если в строке нет ни одной цифры,
	// завершаем выполнения функции
	if (!digits.size()) {
		return;
	}

	// сортируем цифры в порядке уменьшения
	std::sort(digits.begin(), digits.end(), std::greater<int>());
	cout << "-----Found some digits-----\n";
	cout << "All digit in descending order: ";
	
	// выводим все цифры в одну строку
	for (auto d : digits) {
		cout << d << " ";
	}
	cout << std::endl;

	// выводим максимальную и минимальную цифры
	cout << "Max = " << digits.front() << "\t" << "Min = " << digits.back() << std::endl;

	// суммируем все цифры и выводим сумму
	cout << "Sum = " << std::accumulate(digits.begin(), digits.end(), 0) << std::endl;
	cout << "--------------------\n";
}

// функция, обрабатывающая различные команды,
// во время работы сервера
void CommandProcess(Server* l_server) {
	while (l_server->IsRunning()) {
		std::string str;
		std::getline(std::cin, str);
		if ((str == "quit")|| str == "exit") {
			l_server->Stop();
			break;
		}
	}
}

int main() {

    // создаем инстанс объекта сервер,
	// передают ему функцию, отвечающую за обработку входящей строки,
	// и поток для вывода обработанных данных
    Server server(StringHandler, std::cout);


    //пытаемся запустить сервер
    std::cout << "Starting server...\n";
	
	// в случае успешного запуска
	if (server.Start()) {
		// запускам командный поток в отдельной ветви
		std::thread c(CommandProcess, &server);
		c.detach();

		// главный цикл работы сервера
		while (server.IsRunning()) {
			server.Update();
		}
	}

	// сообщаем пользователь об остановке сервера
    std::cout << "Server has been stoped\n";
    return 0;
}
