#pragma once
#include <stdexcept>

class invalidGeneticAlgorithmStopClauseException : public std::logic_error
{
public:
	using _Mybase = logic_error;

	explicit invalidGeneticAlgorithmStopClauseException(const std::string& _Message) : _Mybase(_Message.c_str()) {}

	explicit invalidGeneticAlgorithmStopClauseException(const char* _Message) : _Mybase(_Message) {}

	const char* what() const noexcept override { return logic_error::what(); }
};

