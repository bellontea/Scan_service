#pragma once

#include "../Socket/Socket.h"

class ClientSocket : private Socket
{
public:
	ClientSocket ()= default;;
	explicit ClientSocket (const std::string& socket_path);
	~ClientSocket() override= default;;

	const ClientSocket& operator << (const std::string&) const;
	const ClientSocket& operator >> (std::string&) const;
};
