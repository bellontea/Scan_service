#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

const int MAXCONNECTIONS = 20;
const int MAXRECV = 500;

class Socket
{
public:
	explicit Socket(const std::string& socket_name);
	Socket ()= default;
	virtual ~Socket();

	// Server initialization
	bool create();
	bool bind ();
	bool listen() const;
	bool accept (Socket&) const;

	// Client initialization
	bool connect ();

	// Data Transimission
	bool send (std::string) const;
	int recv (std::string&) const;


	void set_non_blocking (bool);

	bool is_valid() const { return socket_fd != -1; }


private:
	int socket_fd{};
	sockaddr_un socket_addr{};
	socklen_t addr_len{};
	char socket_path[108]{};
};
