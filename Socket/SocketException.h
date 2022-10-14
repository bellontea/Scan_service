#pragma once

#include <string>
#include <utility>

class SocketException
{
private:
	std::string message;

public:
	explicit SocketException (std::string s) : message(std::move(s)) {};
	~SocketException ()= default;

	std::string description() { return message; }
};
