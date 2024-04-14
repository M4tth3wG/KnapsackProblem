#pragma once
#include <stdexcept>

class invalidItemSizeException: public std::logic_error
{
public:
	using _Mybase = logic_error;

	explicit invalidItemSizeException(const std::string& _Message) : _Mybase(_Message.c_str()) {}

	explicit invalidItemSizeException(const char* _Message) : _Mybase(_Message) {}

	const char* what() const noexcept override { return logic_error::what(); }
};

