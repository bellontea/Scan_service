#include "ClientSocket.h"
#include "../Socket/SocketException.h"

ClientSocket::ClientSocket(const std::string& socket_path) : Socket(socket_path)
{
	if (!Socket::create())
		throw SocketException( "Could not create client socket.");

	if (!Socket::connect())
		throw SocketException ("Could not bind to socket address.");
}

const ClientSocket& ClientSocket::operator << (const std::string& s) const
{
	if (!Socket::send(s))
		throw SocketException ("Could not write to socket.");

	return *this;
}


const ClientSocket& ClientSocket::operator >> (std::string& s) const
{
	if (!Socket::recv(s))
		throw SocketException ("Could not read from socket.");

	return *this;
}