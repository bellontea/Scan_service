#include "ServerSocket.h"
#include "../Socket/SocketException.h"
#include <string>
#include <iostream>
#include "Scan.h"

int main()
{
	std::cout << "== Scan service is started ==\n";

	try
	{
		// Создание сокета
		ServerSocket server(SOCKETPATH);

		while (true)
		{
			// Создание сокета для клиента
			ServerSocket new_sock;
			// Принятие поделючения от клиента
			server.accept(new_sock);

			std::string data;
			// Ожидание поступления данных
			while (true)
			{
				new_sock >> data;
				if (!data.empty())
					break;
			}
			// Запуск сканирования и передача результата клиенту
			Scan ob(data);
			new_sock << ob.start_scan();
		}
	}
	catch (SocketException& e)
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}

	return 0;
}