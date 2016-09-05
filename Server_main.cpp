#include "Server/include/Server.hpp"
#include <iostream>
#include <thread>
#include <regex>
#include <vector>
#include <algorithm>
#include <numeric>

void StringHandler(std::ostream& cout, const std::string& l_string) {
	std::vector<int> digits;
	
	std::regex regularExp("[[:digit:]]");
	const std::sregex_token_iterator end;
	for (std::sregex_token_iterator itr(l_string.begin(), l_string.end(), regularExp, 0); itr != end; ++itr) {
		digits.push_back(stoi(*itr));
	}
	if (!digits.size()) {
		return;
	}
	std::sort(digits.begin(), digits.end(), std::greater<int>());
	cout << "-----Found some digits-----\n";
	cout << "All digit in descending order: ";
	for (auto d : digits) {
		cout << d << " ";
	}
	cout << std::endl;
	cout << "Max = " << digits.front() << "\t" << "Min = " << digits.back() << std::endl;
	cout << "Sum = " << std::accumulate(digits.begin(), digits.end(), 0) << std::endl;
	cout << "--------------------\n";
}

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

    //создаем инстанс объекта сервер
    Server server(StringHandler, std::cout);


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
