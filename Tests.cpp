#include "Tests.h"
#include "Individual.h"
#include <iostream>
#include <stdexcept>

void Tests::mutateTest()
{
	Individual individual(5, 0);

	std::cout << individual << "\n";

	individual.mutate(1.0);

	std::cout << individual << "\n";
	
}

void Tests::crossbreedTest()
{
	std::vector<bool> genes1{ 1, 1, 1, 1 };
	std::vector<bool> genes2{ 0, 0, 0, 0 };

	Individual parent1(genes1);
	Individual parent2(genes2);
	
	std::vector<Individual*> children = parent1.crossbreed(parent2);

	std::cout << parent1 << "\n";
	std::cout << parent2 << "\n";

	std::cout << *children[0] << "\n";
	std::cout << *children[1] << "\n";

	delete children[0];
	delete children[1];
}

void Tests::loadProblemTest()
{
	std::vector<std::string> filePaths{"notExistingFile", "test1.txt", "test2.txt", "test3.txt" , "test4.txt", "test5.txt", "test6.txt", "test7.txt", "test8.txt", "test9.txt", "test10.txt" };

	for (std::string& filePath : filePaths) {
		try {
			KnapsackProblem problem(filePath);
		}
		catch (std::exception& e) {
			std::cout << typeid(e).name() << " # " << e.what() << "\n\n";
		}
	}

	
}

void Tests::calculateFitnessTest()
{
	std::vector<Item> items{ Item(1, 1), Item(2, 2), Item(3, 3) };
	KnapsackProblem problem(3, items);

	std::vector<bool> genotype1{ 0, 0, 0 };
	std::vector<bool> genotype2{ 1, 1, 0 };
	std::vector<bool> genotype3{ 1, 1, 1 };

	std::cout << problem.calculateFitness(genotype1) << "\n\n";
	std::cout << problem.calculateFitness(genotype2) << "\n\n";
	std::cout << problem.calculateFitness(genotype3) << "\n\n";



}
