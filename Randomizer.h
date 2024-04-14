#pragma once
#include <random>

class Randomizer
{
public:
	static int randomInteger(int from, int to);
	static bool randomEvent(double probability);

private:
	inline static std::random_device rd = std::random_device();
	inline static std::mt19937 gen = std::mt19937(rd());
	inline static std::uniform_real_distribution<double> realDistrib = std::uniform_real_distribution<double>(0.0, 1.0);
};

