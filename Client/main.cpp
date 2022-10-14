#include "ClientSocket.h"
#include "../Socket/SocketException.h"
#include <iostream>
#include <string>

int main (int argc, char **argv)
{
	if (argc != 2)
		return 1;
	try
	{
		ClientSocket client_socket("serverSocket");
		std::string reply;

		client_socket << argv[1];
		client_socket >> reply;

		std::cout << reply;
	}
	catch (SocketException& e)
	{
		std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}