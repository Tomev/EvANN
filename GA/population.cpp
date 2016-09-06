#include <iostream>
#include "population.h"
#include "Selectors/selectors.h"

// Constructor for neural net oriented population
population::population(unsigned int size, unsigned int iterations,
                       neuralNet* nn, i_distribution* distribution) :
iterations(iterations), distribution(distribution)
{
	// Add proper objective function
	objectiveFunction = new alternativeNeuralWessingersEvaluator(nn);

  // Create factory
  factory = new individualsFactory(nn, distribution);

  // Initialize best solution holder
  bestSolutionHolder = factory->createIndividual();

	// Initialize population

	double individualsError;

	// For each expected individual in the population
	for(unsigned int i = 0; i < size; ++i)
	{
		// Add individual to the population
		individuals.push_back(factory->createIndividual());
		individual* currentIndividual = &individuals.at(i);

		/* Evaluate this individual. Note that currently it is it's error
		 * not it's actual, normalized fitness value. */
		individualsError = objectiveFunction->evaluate(currentIndividual->getSolution());
		currentIndividual->setEvaluationValue(individualsError);

		if(individualsError > highestKnownError)
			highestKnownError = individualsError;
	}

	// Having highest known error begin normalization of the population.
	normalizePopulation(&individuals);

  // Add proper selector
  selector = new rouletteWheelSelector(&individuals, normalizedSimpleScaling);
  //selector = new elitismSelector(elitismSelector::maximizing);
  //selector->setNewPopulation(&individuals);
}

/* It's the main method of the population, which holds all the computing.
 * when it's done best solution is found. */
void population::findSolution()
{
	// DEBUG
	findBestIndividual();
	cout << "Start error = " << objectiveFunction->evaluate(bestIndividual->getSolution()) << endl;
	cout << "Biggest error = " << highestKnownError << endl;
  cout << "Best individual fitness = " << bestIndividual->getFitnessValue() << endl;
	// END DEBUG

	// For each iteration
	for(unsigned int iteration = 0; iteration < iterations; ++iteration )
	{
    findBestIndividual();
    if( objectiveFunction->evaluate(bestIndividual->getSolution()) <
        objectiveFunction->evaluate(bestSolutionHolder.getSolution()))
      bestSolutionHolder.setSolution(bestIndividual->getSolution());

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
	cout << "End error = " << objectiveFunction->evaluate(bestSolutionHolder.getSolution()) << endl;
	cout << "Biggest error = " << highestKnownError << endl;
  cout << "Best individual fitness = " << bestIndividual->getFitnessValue() << endl;
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

    selector->selectParents(&i, &j);

    individual* p1 = &individuals.at(i);
    individual* p2 = &individuals.at(j);

    // Add new individual to offsprings
    offsprings.push_back(factory->createIndividual(p1, p2));
    individual* newIndividual = &offsprings.at(offsprings.size()-1);

    // Evaluate individual
    double individualsError = objectiveFunction->evaluate(newIndividual->getSolution());

	  // Update error data if needed
	  if(individualsError > highestKnownError)
	  {
		  highestKnownError = individualsError;

		  // Normalize populations fitness according to new error
		  normalizePopulation(&offsprings);
		  normalizePopulation(&individuals);
	  }

    // Evaluate new individual
    newIndividual->setFitnessValue(normalize(individualsError));
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
      if(individualsError > highestKnownError)
      {
	      highestKnownError = individualsError;

	      // Normalize populations fitness according to new error
	      normalizePopulation(&offsprings);
	      normalizePopulation(&individuals);
      }

      // Update individuals fitness
      individuals.at(i).setFitnessValue(normalize(individualsError));
    }
  }
}

/* Selects new population from population of offsprings and original
 * mutated population */
void population::selectNewPopulation()
{
  selector->setMaximalValue(highestKnownError);

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
  unsigned int index = 0;

  selector->setNewPopulation(&helperPopulation);

  selector->setNewPopulation(&helperPopulation);

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
	return bestSolutionHolder.getSolution();
}

// Normalize fitness values of whole population to [0,1], where 1 is the most
// desirable fitness.
void population::normalizePopulation(vector<individual>* population)
{
	for(int i = 0; i < population->size(); ++i)
	{
		individual* currentIndividual = &population->at(i);
		currentIndividual->setFitnessValue(normalize(currentIndividual->getEvaluationValue()));
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