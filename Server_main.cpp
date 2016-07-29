//#include "Network.h"
#include "Server.h"
int main() {
	
	//создаем инстанс объекта сервер
	Server server;

	//пытаемся запустить сервер
	server.Start();

	//в случае успешного запуска
	//входим в основной рабочий цикл сервера
	while (server.IsRunning())	{
		server.Update();
	}

	return 0;
}