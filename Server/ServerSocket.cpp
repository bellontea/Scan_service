#include "ServerSocket.h"
#include "../Socket/SocketException.h"

ServerSocket::ServerSocket(const std::string& socket_path) : Socket(socket_path)
{
	if (!Socket::create())
		throw SocketException("Could not create server socket.");

	if (!Socket::bind())
		throw SocketException("Could not bind to port.");

	if (!Socket::listen())
		throw SocketException ("Could not listen to socket.");
}

ServerSocket::~ServerSocket()
= default;


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
	if (!Socket::send(s))
		throw SocketException("Could not write to socket.");

	return *this;
}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
	if (!Socket::recv(s))
		throw SocketException("Could not read from socket.");

	return *this;
}

void ServerSocket::accept(ServerSocket& sock)
{
	if (! Socket::accept ( sock ))
		throw SocketException( "Could not accept socket.");
}

