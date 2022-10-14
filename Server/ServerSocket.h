#pragma once

#include "../Socket/Socket.h"

class ServerSocket : private Socket
{
public:

	ServerSocket()= default;;

	explicit ServerSocket (const std::string& socket_path);
	~ServerSocket() override;

	const ServerSocket& operator << ( const std::string& ) const;
	const ServerSocket& operator >> ( std::string& ) const;

	void accept ( ServerSocket& );

};

