#ifndef GENEVANN_POPULATION_H
#define GENEVANN_POPULATION_H

#include "individual.h"
#include "../ObjectiveFunctions/objectiveFunctions.h"
#include "Selectors/i_selector.h"
#include "individualsFactory.h"

class population {
public:
	population(unsigned int size, unsigned int iterations,
	           neuralNet* nn, i_distribution* distribution);

  void findSolution();

  void* getResult();

protected:
  unsigned int mutationChancePercent = 5;
  unsigned int iterations = 50000;

  std::uniform_int_distribution<> _uniformIntDistribution;
  std::mt19937 _gen;

  // TODO: Change to some kind of smart pointer.
  individual* bestIndividual = nullptr;
  individualsFactory* factory = nullptr;
  i_objectiveFunction* objectiveFunction = nullptr;
  i_selector* selector = nullptr;
  i_distribution* distribution = nullptr;

  vector<individual> individuals;
  vector<individual> offsprings;

  individual bestSolutionHolder;

  void findBestIndividual();
  void createOffspringPopulation();
  void mutateOldPopulation();
  void selectNewPopulation();

	double countFitnessSum();
	double countVariation();
	double countStandardDerivative();
};

#endif //GENEVANN_POPULATION_H
