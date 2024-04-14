#include "GeneticAlgorithm.h"
#include <stdexcept>
#include <iostream>
#include "Randomizer.h"
#include "invalidGeneticAlgorithmPopulationSizeException.h"
#include "invalidGeneticAlgorithmStopClauseException.h"
#include "invalidGeneticAlgorithmCrossProbabilityException.h"
#include "invalidGeneticAlgorithmMutateProbabilityException.h"
#include "geneticAlgorithmBestResaultNotCalculatedException.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, int iterations, double crossProb, double mutProb, KnapsackProblem& problem) : popSize(popSize), iterations(iterations), crossProb(crossProb), mutProb(mutProb), problem(problem)
{
	if (popSize < 1) {
		throw invalidGeneticAlgorithmPopulationSizeException("Invalid population size!");
	}
	if (iterations < 1) {
		throw invalidGeneticAlgorithmStopClauseException("Invalid iterations stop clause!");
	}
	if (crossProb < 0 || crossProb > 1) {
		throw invalidGeneticAlgorithmCrossProbabilityException("Invalid crossing probability!");
	}
	if (mutProb < 0 || mutProb > 1) {
		throw invalidGeneticAlgorithmMutateProbabilityException("Invalid mutation probability!");
	}
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& other) : popSize(other.popSize), iterations(other.iterations), crossProb(other.crossProb), mutProb(other.mutProb), problem(other.problem), bestResault(other.bestResault) 
{
	erasePopulation();

	for (int i = 0; i < other.population.size(); i++) {
		population.push_back(new Individual(*(other.population[i])));
	}
}


GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithm&& other) : popSize(other.popSize), iterations(other.iterations), crossProb(other.crossProb), mutProb(other.mutProb), problem(other.problem), bestResault(other.bestResault) {
	
	erasePopulation();

	for (int i = 0; i < other.population.size(); i++) {
		population.push_back(other.population[i]);
		other.population[i] = nullptr;
	}
}

GeneticAlgorithm& GeneticAlgorithm::operator=(GeneticAlgorithm other)
{

	popSize = other.popSize;
	iterations = other.iterations;
	crossProb = other.crossProb;
	mutProb = other.mutProb;
	problem = other.problem;
	bestResault = other.bestResault;
	std::swap(population, other.population);

	return *this;
}

GeneticAlgorithm& GeneticAlgorithm::operator=(GeneticAlgorithm&& other)
{
	popSize = other.popSize;
	iterations = other.iterations;
	crossProb = other.crossProb;
	mutProb = other.mutProb;
	problem = other.problem;
	bestResault = other.bestResault;
	std::swap(population, other.population);

	return *this;
}

void GeneticAlgorithm::optimize()
{
	erasePopulation();
	generateInitialPopulation();

	for (int i = 0; i < iterations; i++) {
		evaluatePopulationFitness();
		generateNewPopulation();
	}
}

void GeneticAlgorithm::optimize(double itemDensity)
{
	erasePopulation();
	generateInitialPopulation(itemDensity);

	for (int i = 0; i < iterations; i++) {
		evaluatePopulationFitness();
		generateNewPopulation();
	}
}

void GeneticAlgorithm::generateInitialPopulation()
{
	for (int i = 0; i < popSize; i++) {
		population.push_back(new Individual(problem.getNumOfItems()));
	}
}

void GeneticAlgorithm::generateInitialPopulation(double itemDensity)
{
	if (itemDensity < 0.0 || itemDensity > 1.0) {
		throw std::invalid_argument("Invalid item density!");
	}

	for (int i = 0; i < popSize; i++) {
		population.push_back(new Individual(problem.getNumOfItems(), itemDensity));
	}
}

void GeneticAlgorithm::evaluatePopulationFitness()
{
	Individual* resault = population[0];

	for (int i = 0; i < popSize; i++) {
		population[i]->calculateFitness(problem);

		if (resault->getFitness(problem) < population[i]->getFitness(problem)) {
			resault = population[i];
		}
	}
	if (!bestResault.has_value() || bestResault.value().getFitness(problem) < resault->getFitness(problem)) {
		bestResault = *resault;
	}
	
}

Individual* GeneticAlgorithm::drawIndividual() const
{
	Individual* first = population[Randomizer::randomInteger(0, popSize - 1)];
	Individual* second = population[Randomizer::randomInteger(0, popSize - 1)];

	if (first->getFitness(problem) >= second->getFitness(problem)) {
		return first;
	}
	return second;
}

void GeneticAlgorithm::generateNewPopulation()
{
	std::vector<Individual*> newPopulation;

	while (newPopulation.size() < popSize) {
		std::vector<Individual*> children = createChildren();
		newPopulation.push_back(children[0]);

		if (newPopulation.size() < popSize) {
			newPopulation.push_back(children[1]);
		}
		else {
			delete children[1];
		}
	}
	erasePopulation();
	population = newPopulation;
}

void GeneticAlgorithm::erasePopulation()
{
	for (int i = 0; i < population.size(); i++) {
		delete population[i];
	}
	population.clear();
}

std::pair<std::vector<bool>, double> GeneticAlgorithm::getBestResault()
{
	if (!bestResault.has_value()) {
		throw geneticAlgorithmBestResaultNotCalculatedException("Best resault not calculated!");
	}
	
	return std::pair<std::vector<bool>, double>(bestResault.value().getGenotype(), bestResault.value().getFitness(problem));
}

void GeneticAlgorithm::printBestResult()
{
	if (!bestResault.has_value()) {
		throw geneticAlgorithmBestResaultNotCalculatedException("Best resault not calculated!");
	}
	else {
		std::cout << bestResault.value();
	}
}

std::vector<Individual*> GeneticAlgorithm::createChildren() const
{
	Individual* first = drawIndividual();
	Individual* second = drawIndividual();
	std::vector<Individual*> children;

	if (Randomizer::randomEvent(crossProb)) {
		children = first->crossbreed(*second);
	}
	else {
		children.push_back(new Individual(*first));
		children.push_back(new Individual(*second));
	}
	
	children.at(0)->mutate(mutProb);
	children.at(1)->mutate(mutProb);

	return children;
}
