#include "Individual.h"
#include <iostream>
#include "Randomizer.h"

Individual::Individual(int numOfGenes) : numOfGenes(numOfGenes) {

	for (int i = 0; i < numOfGenes; i++) {
		genotype.push_back(Randomizer::randomInteger(0, 1));
	}
}

Individual::Individual(int numOfGenes, double itemDensity) : numOfGenes(numOfGenes) {

	for (int i = 0; i < numOfGenes; i++) {
		genotype.push_back(false);
	}

	int positiveGenes = 0;
	int positiveGenesTarget = itemDensity * numOfGenes;

	while (positiveGenes < positiveGenesTarget) {
		int index = Randomizer::randomInteger(0, numOfGenes - 1);

		if (genotype[index] == false) {
			genotype[index] = true;
			positiveGenes++;
		}
	}
}

Individual::Individual(std::vector<bool>& genotype): genotype(genotype), numOfGenes(genotype.size()) {}

Individual::Individual(const Individual& other) : numOfGenes(other.numOfGenes), genotype(other.genotype), fitness(other.fitness) {}

Individual::Individual(Individual&& other): numOfGenes(other.numOfGenes), genotype(other.genotype), fitness(other.fitness) {}

Individual::~Individual() {}

Individual& Individual::operator=(const Individual& other)
{
	if (this == &other) {
		return *this;
	}
	
	numOfGenes = other.numOfGenes;
	genotype = other.genotype;
	fitness = other.fitness;

	return *this;
}

Individual& Individual::operator=(Individual&& other)
{
	numOfGenes = other.numOfGenes;
	genotype = other.genotype;
	fitness = other.fitness;

	return *this;
}

void Individual::mutate(double mutProb)
{
	
	for (int i = 0; i < numOfGenes; i++) {
		if (Randomizer::randomEvent(mutProb)) {
			genotype[i] = !(genotype[i]);
		}
	}
}

std::vector<Individual*> Individual::crossbreed(const Individual& other) const
{
	Individual* firstChild = new Individual(*this);
	Individual* secondChild = new Individual(other);

	for (int i = Randomizer::randomInteger(1, numOfGenes - 1); i < numOfGenes && numOfGenes != 1; i++) {
		std::iter_swap(firstChild->genotype.begin() + i, secondChild->genotype.begin() + i);
	}

	std::vector<Individual*> children;
	children.push_back(firstChild);
	children.push_back(secondChild);
	
	return children;
}

double Individual::calculateFitness(const KnapsackProblem& problem)
{
	fitness = problem.calculateFitness(genotype);
	return fitness.value();
}

double Individual::getFitness(const KnapsackProblem& problem)
{
	if (!fitness.has_value()) {
		calculateFitness(problem);
	}
	return fitness.value();
}

std::ostream& operator<<(std::ostream& os, const Individual& other)
{
	os << "Individual:\n\tgenotype:\t";

	for (int i = 0; i < other.genotype.size(); i++) {
		os << other.genotype[i] << " ";
	}

	os << "\n\tfitness:\t";
	
	if (other.fitness.has_value()) {
		os << other.fitness.value();
	}
	else {
		os << "NOT CALCULATED";
	}
	

	return os;
}
