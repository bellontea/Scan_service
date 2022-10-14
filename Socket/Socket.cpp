#include "Socket.h"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <iostream>


Socket::Socket(const std::string& socket_name) : socket_fd(-1)
{
	memset (&socket_addr,0,sizeof(socket_addr));
	socket_addr.sun_family = AF_UNIX;
	socket_addr.sun_path[0] = 0;
	std::strcpy (socket_path, socket_name.c_str());
	strcpy(socket_addr.sun_path+1,socket_path);
	addr_len = sizeof(socket_addr.sun_family) + sizeof(socket_path);
}

Socket::~Socket()
{
	if (is_valid())
		::close(socket_fd);
}

bool Socket::create()
{
	socket_fd = socket (AF_UNIX,SOCK_SEQPACKET,0);
	if (!is_valid())
		return false;
	return true;

}



bool Socket::bind()
{
	if (!is_valid())
		return false;

	int bind_return = ::bind(socket_fd,(struct sockaddr*) &socket_addr,addr_len);
	if (bind_return == -1)
		return false;

	return true;
}


bool Socket::listen() const
{
	if (!is_valid())
		return false;

	int listen_return = ::listen (socket_fd, MAXCONNECTIONS);

	if (listen_return == -1)
		return false;

	return true;
}


bool Socket::accept(Socket& new_socket) const
{
	int addr_length = sizeof(sockaddr_un);
	new_socket.socket_fd = ::accept(socket_fd, (sockaddr *) &socket_addr, (socklen_t *) &addr_length);

	if (new_socket.socket_fd <= 0 )
		return false;
	return true;
}


bool Socket::send (std::string s) const
{
	int status = ::send(socket_fd, s.c_str(), s.size(), MSG_NOSIGNAL);
	if (status == -1)
		return false;
	return true;
}


int Socket::recv(std::string& s) const
{
	char buf[MAXRECV + 1];
	s = "";
	memset (buf, 0, MAXRECV + 1);

	int status = ::recv(socket_fd, buf, MAXRECV, 0);

	if (status == -1)
	{
		std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
		return 0;
	}
	else if (!status)
		return 0;

	s = buf;
	return status;
}

bool Socket::connect()
{
	if (!is_valid())
		return false;

	int status = ::connect(socket_fd, ( sockaddr * ) &socket_addr, addr_len);

	if (status == 0)
		return true;
	return false;
}

void Socket::set_non_blocking(bool b)
{
	int flags;
	flags = fcntl(socket_fd,F_GETFL);
	if (flags < 0)
		return;

	if (b)
		flags = (flags | O_NONBLOCK);
	else
		flags = (flags & ~O_NONBLOCK );

	fcntl(socket_fd,F_SETFL, flags);
}