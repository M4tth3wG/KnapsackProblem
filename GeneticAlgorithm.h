#pragma once
#include <optional>
#include <iostream>
#include "Individual.h"
#include "KnapsackProblem.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, int iterations, double crossProb, double mutProb, KnapsackProblem& problem);
	GeneticAlgorithm(const GeneticAlgorithm& other);
	GeneticAlgorithm(GeneticAlgorithm&& other);
	~GeneticAlgorithm() { erasePopulation(); }

	GeneticAlgorithm& operator=(GeneticAlgorithm other);
	GeneticAlgorithm& operator=(GeneticAlgorithm&& other);

	void optimize();
	void optimize(double itemDensity);
	std::pair<std::vector<bool>, double> getBestResault();
	void printBestResult();

private:
	int popSize;
	int iterations;
	double crossProb;
	double mutProb;
	std::vector<Individual*> population;
	KnapsackProblem& problem;
	std::optional<Individual> bestResault;

	void generateInitialPopulation();
	void generateInitialPopulation(double itemDensity);
	void evaluatePopulationFitness();
	void erasePopulation();
	Individual* drawIndividual() const;
	void generateNewPopulation();
	std::vector<Individual*> createChildren() const;
};

