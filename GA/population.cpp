#include <iostream>
#include "population.h"
#include "Selectors/selectors.h"

// Constructor for neural net oriented population
population::population(unsigned int size, unsigned int iterations,
                       neuralNet* nn, i_distribution* distribution) :
iterations(iterations), distribution(distribution)
{
  std::random_device rd;
  _gen = std::mt19937(rd());
  _uniformIntDistribution = std::uniform_int_distribution<>(0, 100);

	// Add proper objective function
	objectiveFunction = new alternativeNeuralWessingersEvaluator(nn);

  // Create factory
  factory = new individualsFactory(nn, distribution);

  // Initialize best solution holder
  bestSolutionHolder = factory->createIndividual();
  bestSolutionHolder.setFitnessValue(objectiveFunction->evaluate(bestSolutionHolder.getSolution()));

	// Initialize population

	// For each expected individual in the population
	for(unsigned int i = 0; i < size; ++i) {
    // Add individual to the population
    individuals.push_back(factory->createIndividual());
    individual * currentIndividual = &individuals.at(i);

    /* Evaluate this individual. Note that currently it is it's error
     * not it's actual, normalized fitness value. */
    currentIndividual->setFitnessValue(objectiveFunction->evaluate(currentIndividual->getSolution()));
  }

  // Add proper selector
  selector = new rouletteWheelSelector(&individuals, normalizedSimpleScaling);
  selector->setMaximalValue(1); // As it's now fixed and handled by objective function
}

/* It's the main method of the population, which holds all the computing.
 * when it's done best solution is found. */
void population::findSolution()
{
	// DEBUG
	findBestIndividual();
  cout << "Standard deviation = " << countStandardDeviation() << endl;
  vector<double> convergence = {};
	// END DEBUG

	// For each iteration
	for(unsigned int iteration = 0; iteration < iterations; ++iteration )
	{
    findBestIndividual();

    if( bestIndividual->getFitnessValue() > bestSolutionHolder.getFitnessValue() ){
      bestSolutionHolder.setSolution(bestIndividual->getSolution());
      bestSolutionHolder.setFitnessValue(bestIndividual->getFitnessValue());
    }

    createOffspringPopulation();

    mutateOldPopulation();

    // Select next population from individuals of both populations
    selectNewPopulation();

    // Show that application is working by printing "." after 100 iterations.
    if(fmod(iteration, iterations / 10) == 0) {
      convergence.push_back(countFitnessSum() / individuals.size());
      cout << "Iteration " << iteration << ": " << convergence.back() << endl;
    }
	}

	cout << endl;

	// Find best individual in final population
	findBestIndividual();

	// DEBUG
  cout << "Standard deviation = " << countStandardDeviation() << endl << "Convergence: " << endl;
  for(auto val : convergence)
    cout << val << endl;
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

    // Evaluate new individual
    newIndividual->setFitnessValue(objectiveFunction->evaluate(newIndividual->getSolution()));
  }
}

// Mutate individuals in old population basing on given mutation chance
void population::mutateOldPopulation()
{
  unsigned int mutationRollValue;
  // For each individual in the population
  for(auto individual : individuals)
  {
    // Roll for mutation
    mutationRollValue = _uniformIntDistribution(_gen);

    // Mutate i-th individual if mutation occurred
    if(mutationRollValue <= mutationChancePercent)
    {
      individual.mutate();

      // Update individuals fitness
      individual.setFitnessValue(objectiveFunction->evaluate(individual.getSolution()));
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
  unsigned int index = 0;

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
											& individuals.at(i) : bestIndividual;
	}
}

double population::countFitnessSum()
{
  double sum = 0.0;

  for(auto individual : individuals) sum += individual.getFitnessValue();

  return sum;
}

double population::countVariation()
{
  double variation = 0.0;
  double average = countFitnessSum() / individuals.size();;

  for(auto individual : individuals) variation += pow(individual.getFitnessValue() - average ,2);

  variation /= individuals.size();

  return variation;
}

double population::countStandardDeviation()
{
  return sqrt(countVariation());
}
