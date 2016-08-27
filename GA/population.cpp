#include <iostream>
#include "population.h"
#include "Selectors/rouletteWheelSelector.h"
#include "Selectors/ScalingFunctions/scalingFunctions.h"

// Constructor for neural net oriented population
population::population(unsigned int size, neuralNet* nn, i_distribution* distribution) :
distribution(distribution)
{
	// Add proper objective function
	objectiveFunction = new neuralWessingerEvaluator(nn);

  // Create factory
  factory = new individualsFactory(nn, distribution);

	// Initialize population

	// For each expected individual in the population
	for(unsigned int i = 0; i < size; ++i)
	{
		// Add individual to the population
		individuals.push_back(factory->createIndividual());
		individual* currentIndividual = &individuals.at(i);
    currentIndividual->print();

		/* Evaluate this individual. Note that currently it is it's error
		 * not it's actual, normalized fitness value. */
		currentIndividual->setFitnessValue(objectiveFunction->evaluate(currentIndividual->getSolution()));
	}

	/* Find individual with the highest error. findBestIndividual() can
	 * be used, as fitness value of each individual holds it's error now. */
	findBestIndividual();

	highestKnownError = bestIndividual->getFitnessValue();

	// Having highest known error begin normalization of the population.
	normalizePopulation();

  // Add proper selector
  selector = new rouletteWheelSelector(&individuals, normalizedSimpleScaling);
}

/* It's the main method of the population, which holds all the computing.
 * when it's done best solution is found. */

void population::findSolution()
{
	// DEBUG
	findBestIndividual();
	cout << "Start error = " << objectiveFunction->evaluate(bestIndividual->getSolution()) << endl;
	cout << "Biggest error = " << highestKnownError << endl;
	// END DEBUG

	// For each iteration
	for(unsigned int iteration = 0; iteration < iterations; ++iteration )
	{

    createOffspringPopulation();
    mutateOldPopulation();

    // Select next population from individuals of both populations
    selectNewPopulation();

    // Show that application is working by printing "." after each iteration.
		cout << ".";
	}

	cout << endl;

	// Find best individual in final population
	findBestIndividual();

	// DEBUG
	cout << "Start end = " << objectiveFunction->evaluate(bestIndividual->getSolution()) << endl;
	cout << "Biggest error = " << highestKnownError << endl;
	// END DEBUG
}

void population::createOffspringPopulation()
{
  // Clear offsprings vector
  offsprings.clear();

  /* Add new offspring to the offsprings vector until its size is equal
   * to the size of the population. */

  // Parent indexes
  unsigned int i, j;

  while(offsprings.size() < individuals.size())
  {
    // Select two parents.
    i = selector->selectIndividual();
    j = selector->selectIndividual();

    // Ensure DIFFERENT parents are selected
    while(i == j) j = selector->selectIndividual();

    individual* p1 = &individuals.at(i);
    individual* p2 = &individuals.at(j);

    // Add new individual to offsprings
    offsprings.push_back(factory->createIndividual(p1, p2));
  }
}

// Mutate individuals in old population basing on given mutation chance
void population::mutateOldPopulation()
{
  unsigned int mutationRollValue;
  // For each individual in the population
  for(unsigned int i = 0; i < individuals.size(); ++i)
  {
    // Roll for mutation
    mutationRollValue = rand() % 100 + 1;

    // Mutate i-th individual if mutation occurred
    if(mutationRollValue <= mutationChancePercent)
    {
      individuals.at(i).mutate();

      // Evaluate individual
      double individualsError = objectiveFunction->evaluate(individuals.at(i).getSolution());

      // Update error data if needed
      highestKnownError =
        (individualsError > highestKnownError) ?
         individualsError : highestKnownError;

      // Update individuals fitness
      individuals.at(i).setFitnessValue(normalize(individualsError));

    }
  }
}

/* Selects new population from population of offsprings and original
 * mutated population */
void population::selectNewPopulation()
{
  // Remember population size
  unsigned int size = individuals.size();

  // Create helper population for selector containing both populations
  vector<individual> helperPopulation;

  // For each individual in both populations
  for(unsigned int i = 0; i < individuals.size(); ++i)
  {
    /* Knowing that both offspring and individuals has same size
     * one loop can be used to transfer individuals of both to helper. */

    helperPopulation.push_back(individuals.at(i));
    helperPopulation.push_back(offsprings.at(i));
  }

  // Clear individuals to make place for next population
  individuals.clear();

  // Fill next population until its size is equal to the original size
  unsigned int index;

  while(individuals.size() < size)
  {
    // Select individual
    index = selector->selectIndividual();
    // Add it to next population
    individuals.push_back(helperPopulation.at(index));

    /* Remove added individual from helper population to ensure
     * that it occurs only once in next population. */
    helperPopulation.erase(helperPopulation.begin() + index);
  }

  // Clear offsprings and helperPopulation
  offsprings.clear();
  helperPopulation.clear();

  // Set selectors population to original population
  selector->setNewPopulation(&individuals);
}

// Returns solution represented by the best found individual
void* population::getResult()
{
	return bestIndividual->getSolution();
}

// Normalize fitness values of whole population to [0,1], where 1 is the most
// desirable fitness.
void population::normalizePopulation()
{
	for(int i = 0; i < individuals.size(); ++i)
	{
		individual* currentIndividual = &individuals.at(i);
		currentIndividual->setFitnessValue(normalize(currentIndividual->getFitnessValue()));
	}
}

// Normalizing target value according to biggest known error.
double population::normalize(double target)
{
	return 1 - (target / highestKnownError);
}

// Method used to find best individual in the population.
// Best individual is the one with highest fitness value.
void population::findBestIndividual()
{
	// Set first individual as best one
	bestIndividual = &individuals.at(0);

	// For each other individual in population
	for(unsigned int i = 1; i < individuals.size(); ++i)
	{
		bestIndividual = (individuals.at(i).getFitnessValue() > bestIndividual->getFitnessValue()) ?
											&individuals.at(i) : bestIndividual;
	}
}