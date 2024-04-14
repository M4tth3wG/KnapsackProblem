#include "Randomizer.h"
#include <random>

int Randomizer::randomInteger(int from, int to)
{
    std::uniform_int_distribution<> intDistrib(from, to);

    return intDistrib(gen);
}

bool Randomizer::randomEvent(double probability)
{
    return realDistrib(gen) <= probability;
}
