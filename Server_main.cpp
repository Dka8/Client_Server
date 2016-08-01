#include "Server/include/Server.hpp"
#include <iostream>

int main() {

    //создаем инстанс объекта сервер
    Server server;


    //пытаемся запустить сервер
    std::cout << "Starting server...\n";
    server.Start();

    //в случае успешного запуска
    //входим в основной рабочий цикл сервера
    while (server.IsRunning())	{
        server.Update();
    }

    std::cout << "Server has been stoped\n";
    return 0;
}
