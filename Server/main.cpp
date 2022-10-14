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
		// Create the socket
		ServerSocket server("serverSocket");

		while (true)
		{
			ServerSocket new_sock;
			server.accept (new_sock);

			std::string data;
			while (true)
			{
				new_sock >> data;
				if (!data.empty())
					break;
			}
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