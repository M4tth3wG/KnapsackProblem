// TEP_Lab_Knapsack_Projekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Item.h";
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include "Tests.h"

int main()
{
    //std::string filePath = "knapPI_1_100_1000_1";
    std::string filePath = "problem.txt";
    int popSize = 100;
    int iterations = 100;
    double crossProb = 0.6;
    double mutProb = 0.001;
    double itemDensity = 0.05;

    try {
        KnapsackProblem problem(filePath);
        GeneticAlgorithm algorithm(popSize, iterations, crossProb, mutProb, problem);

        algorithm.optimize(/*itemDensity*/);
        algorithm.printBestResult();
    }
    catch(std::exception& e) {
        std::cout << typeid(e).name() << " # " << e.what();
    }


    //Tests::mutateTest();
    //Tests::crossbreedTest();
    //Tests::loadProblemTest();
    //Tests::calculateFitnessTest();
    
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
