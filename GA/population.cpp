#include "population.h"

double normalizeValue(double target, double highestValue);

// Adds new individual of given topology to population
void population::addIndividual(vector<int> *topology, i_distribution *distribution)
{
	individuals.push_back(individual(topology, distribution));
}

// Normalize fitness values of whole population to [0,1], where 1 is the most
// desirable fitness.
void population::normalizeFitnesses()
{
	double highestFitnessValue = findHighestFitnessValue();

	for(int i = 0; i < individuals.size(); ++i)
	{
		individuals.at(i).setFitnessValue(
						normalizeValue(individuals.at(i).getFitnessValue(), highestFitnessValue)
		);
	}
}

// Finds value of highest fitness value of individual.
// Note that the lowest possible value is 0.0.
double population::findHighestFitnessValue()
{
	double highestFitnessValue = 0.0;

	for(int i = 0; i < individuals.size(); ++i)
	{
		highestFitnessValue = (individuals.at(i).getFitnessValue() > highestFitnessValue)
													?	individuals.at(i).getFitnessValue() : highestFitnessValue;
	}

	return highestFitnessValue;
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

double normalizeValue(double target, double highestValue)
{
	return 1 - (target / highestValue);
}