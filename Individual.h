#pragma once
#include <random>
#include <optional>
#include "KnapsackProblem.h"

class Individual
{
public:
	Individual(int numOfGenes);
	Individual(int numOfGenes, double itemDensity);
	Individual(std::vector<bool>& genotype);
	Individual(const Individual& other);
	Individual(Individual&& other);
	~Individual();

	Individual& operator=(const Individual& other);
	Individual& operator=(Individual&& other);
	friend std::ostream& operator<<(std::ostream& os, const Individual& other);

	void mutate(double mutProb);
	std::vector<Individual*> crossbreed(const Individual& other) const;
	double calculateFitness(const KnapsackProblem& problem);
	std::vector<bool>& getGenotype() { return genotype; };
	int getNumOfGenes() const{ return numOfGenes; };
	double getFitness(const KnapsackProblem& problem);


private:
	std::vector<bool> genotype;
	std::optional<double> fitness;
	int numOfGenes;
};

