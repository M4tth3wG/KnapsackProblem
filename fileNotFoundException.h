#pragma once
#include <stdexcept>

class fileNotFoundException: public std::exception
{
public:
	using _Mybase = exception;

	explicit fileNotFoundException(const std::string& _Message) : _Mybase(_Message.c_str()) {}

	explicit fileNotFoundException(const char* _Message) : _Mybase(_Message) {}

	const char* what() const noexcept override { return exception::what(); }
};

