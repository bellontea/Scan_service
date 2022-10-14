#include "Socket.h"
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <iostream>

/* Класс для реализации сокета в linux. Используются unix sockets с абстрактным путем */
Socket::Socket(const std::string& socket_name) : socket_fd(-1)
{
	memset(&socket_addr,0,sizeof(socket_addr));
	socket_addr.sun_family = AF_UNIX;
	/* Установление первого байта значением 0 в пути позволяет сделать путь абстрактным */
	socket_addr.sun_path[0] = 0;
	std::strcpy (socket_path, socket_name.c_str());
	strcpy(socket_addr.sun_path + 1,socket_path);
	addr_len = sizeof(socket_addr.sun_family) + sizeof(socket_path);
}

Socket::~Socket()
{
	if (is_valid())
		::close(socket_fd);
}

/* Создание сокета */
bool Socket::create()
{
	socket_fd = socket (AF_UNIX,SOCK_SEQPACKET,0);
	if (!is_valid())
		return false;
	return true;
}

/* Привязывание сокету имени (адреса). После этого клиент сможет его увидеть */
bool Socket::bind()
{
	if (!is_valid())
		return false;

	if (::bind(socket_fd,(struct sockaddr*) &socket_addr,addr_len) == -1)
		return false;

	return true;
}

/* Ввод сокета в режим ожидания (прослушивания запросов на сокете) */
bool Socket::listen() const
{
	if (!is_valid())
		return false;

	if (::listen(socket_fd, MAXCONNECTIONS) == -1)
		return false;

	return true;
}

/* Функция для принятия связи на сокет */
bool Socket::accept(Socket& new_socket) const
{
	int addr_length = sizeof(sockaddr_un);
	new_socket.socket_fd = ::accept(socket_fd, (sockaddr *) &socket_addr, (socklen_t *) &addr_length);

	if (new_socket.socket_fd <= 0 )
		return false;

	return true;
}

/* Запись данных в сокет */
bool Socket::send (std::string s) const
{
	if (::send(socket_fd, s.c_str(), s.size(), MSG_NOSIGNAL) == -1)
		return false;

	return true;
}

/* Чтения данных из сокета */
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

/* Подключение к сокету */
bool Socket::connect()
{
	if (!is_valid())
		return false;

	if (::connect(socket_fd, (sockaddr *) &socket_addr, addr_len) == 0)
		return true;

	return false;
}
