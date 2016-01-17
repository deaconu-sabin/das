

#include "NumberGenerator.h"
#include <cstdlib>

double NumberGenerator::GenerateReal()
{
	return GenerateInt() + (double)rand() / RAND_MAX;
}
double NumberGenerator::GenerateReal(int min, int max)
{
	return GenerateInt(min, max-1) + (double)rand() / RAND_MAX;
}

int NumberGenerator::GenerateInt()
{
	return rand() - (RAND_MAX/2);
}
int NumberGenerator::GenerateInt(int min, int max)
{
	int range = max - min;
	return min + rand() % range;
}

std::vector<double> GenerateDistribution(int    size,
										double 	deviation,
										double 	mean)
{
	std::vector<double> numbers(size);


	return numbers;
}
