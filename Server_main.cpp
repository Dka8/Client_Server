//#include "Network.h"
#include "Server.h"
int main() {
	
	//������� ������� ������� ������
	Server server;

	//�������� ��������� ������
	server.Start();

	//� ������ ��������� �������
	//������ � �������� ������� ���� �������
	while (server.IsRunning())	{
		server.Update();
	}

	return 0;
}