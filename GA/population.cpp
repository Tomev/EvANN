#include "population.h"

void population::initialize(int n)
{
	for(int i = 0; i < populationSize; ++i)
	{
		individuals.push_back(individual());
		individuals.at(i).initialize();
	}
}