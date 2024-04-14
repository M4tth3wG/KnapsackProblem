#include "KnapsackProblem.h"
#include "invalidNumberOfArgumentsException.h"
#include "invalidKnapsackCapacityException.h"
#include "invalidItemValueException.h"
#include "invalidKnapsackNumberOfItemsException.h"
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <regex>
#include "invalidItemSizeException.h"
#include "fileNotFoundException.h"

KnapsackProblem::KnapsackProblem(double capacity, std::vector<Item>& items): capacity(capacity), items(items)
{
	if (capacity <= 0) {
		throw invalidKnapsackCapacityException("Invalid knapsack capacity!");
	}
	if (items.size() == 0) {
		throw invalidKnapsackNumberOfItemsException("Invalid number of items in problem!");
	}
}

KnapsackProblem::KnapsackProblem(std::string& filePath): capacity(0.0), items(std::vector<Item>()) {
	loadProblem(filePath);
}

KnapsackProblem::KnapsackProblem(const KnapsackProblem& other) : capacity(other.capacity), items(other.items) {}

KnapsackProblem::KnapsackProblem(KnapsackProblem&& other) : capacity(other.capacity), items(other.items) {}

KnapsackProblem& KnapsackProblem::operator=(const KnapsackProblem& other)
{
	if (this == &other) {
		return *this;
	}

	capacity = other.capacity;
	items = other.items;

	return *this;
}

KnapsackProblem& KnapsackProblem::operator=(KnapsackProblem&& other)
{
	capacity = other.capacity;
	items = other.items;

	return *this;
}

double KnapsackProblem::calculateFitness(const std::vector<bool>& genotype) const
{
	double fitness = 0;
	double size = 0;

	for (int i = 0; i < genotype.size(); i++) {
		if (genotype[i]) {
			fitness += getItemValue(i);
			size += getItemSize(i);
		}
	}

	if (size > capacity) {
		fitness = 0.0;
	}

	return fitness;
}

void KnapsackProblem::loadProblem(std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::vector<Item> items;
	std::regex delim("\\s+");
	std::regex validator("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$");
	std::vector<std::string> tokens;
	int index = 0;

	if (stream.fail()) {
		throw fileNotFoundException("Invalid file path: " + filePath);
	}

	// capacity
	std::getline(stream, line);
	std::sregex_token_iterator iter(line.begin(), line.end(), delim, -1);
	std::sregex_token_iterator end;
	tokens = { iter, end };

	if (tokens.size() == 1) {
		index = 0;
	}
	else if (tokens.size() == 2 && tokens[0] == "") {
		index = 1;
	}
	else {
		throw invalidNumberOfArgumentsException("Line 1: " + line);
	}

	
	if (std::regex_match(tokens[index], validator)) {
		capacity = stod(tokens[index]);
	}
	else {
		throw invalidKnapsackCapacityException("Line 1: " + line);
	}
		
	
	if (capacity <= 0.0) {
		throw invalidKnapsackCapacityException("Line 1: " + line); 
	}
	
	//items
	double value = 0;
	double size = 0;

	for (int lineNr = 2; std::getline(stream, line); lineNr++) {
		
		

		std::sregex_token_iterator iter(line.begin(), line.end(), delim, -1);
		std::sregex_token_iterator end;
		tokens = {iter, end};

		//tokens
		if (tokens.size() == 1 && tokens[0] == "") {
			continue;
		}
		else if (tokens.size() == 2 && tokens[0] != "") {
			index = 0;
		}
		else if (tokens.size() == 3 && tokens[0] == "") {
			index = 1;
		}
		else {
			throw invalidNumberOfArgumentsException("Line " + std::to_string(lineNr) + ": " + line);
		}

		//value
		if (std::regex_match(tokens[index], validator)) {
			value = stod(tokens[index]);
		}
		else {
			throw invalidItemValueException("Line " + std::to_string(lineNr) + ": " + line);
		}

		//size
		if (std::regex_match(tokens[index + 1], validator)) {
			size = stod(tokens[index + 1]);
		}
		else {
			throw invalidItemSizeException("Line " + std::to_string(lineNr) + ": " + line);
		}

		//item
		try {
			items.push_back(Item(value, size));
		}
		catch (invalidItemSizeException& exception) {
			throw invalidItemSizeException("Line " + std::to_string(lineNr) + ": " + line);
		}
		catch (invalidItemValueException& exception) {
			throw invalidItemValueException("Line " + std::to_string(lineNr) + ": " + line);
		}
		
	}

	this->items = items;
	stream.close();

	if (items.size() == 0) {
		throw invalidKnapsackNumberOfItemsException("Invalid number of items in problem!");
	}
}
