#include "population.h"

// Initialize population with selected number of newly initialized individuals
// of selected topology. Same topology as NN can be used.
void population::initialize(int populationSize, vector<int> *topology)
{
	for(unsigned int i = 0; i < populationSize; ++i)
	{
		individuals.push_back(individual(topology));
		individuals.at(i).initialize();
	}
}

// For debug purposes.
string population::toString()
{
	string result = "";

	for(unsigned int i = 0; i < individuals.size(); ++i)
	{
		result += "Individual " + to_string(i) + ":\n";
		result += individuals.at(i).toString();
	}

	return result;
}