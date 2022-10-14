#include "ClientSocket.h"
#include "../Socket/SocketException.h"
#include <iostream>
#include <string>

int main (int argc, char **argv)
{
	// Проверка на количество введенных аргументов
	if (argc != 2)
		return 1;
	try
	{
		// Создания сокета клиента
		ClientSocket client_socket(SOCKETPATH);
		std::string reply;

		// Передача пути для сканирования и получение ответа
		client_socket << argv[1];
		client_socket >> reply;

		// Вывод ответа в консоль
		std::cout << reply;
	}
	catch (SocketException& e)
	{
		std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}