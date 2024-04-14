#pragma once
#include "Item.h"
#include <vector>
#include <string>

class KnapsackProblem
{
public:
	KnapsackProblem(double capacity, std::vector<Item>& items);
	KnapsackProblem(std::string& filePath);
	KnapsackProblem(const KnapsackProblem& other);
	KnapsackProblem(KnapsackProblem&& other);
	~KnapsackProblem() {}
	
	KnapsackProblem& operator=(const KnapsackProblem& other);
	KnapsackProblem& operator=(KnapsackProblem&& other);

	double calculateFitness(const std::vector<bool>& genotype) const;
	double getItemValue(int indx) const { return items.at(indx).value; }
	double getItemSize(int indx) const { return items.at(indx).size; }
	int getNumOfItems() const { return items.size(); }
	double getCapacity() const { return capacity; }
private:
	std::vector<Item> items;
	double capacity;

	void loadProblem(std::string& filePath);
};

