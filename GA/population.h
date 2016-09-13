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
	double highestKnownError = 0.0;
  unsigned int mutationChancePercent = 5;
  unsigned int iterations = 50000;

  // TODO: Change to some kind of smart pointer.
  individual* bestIndividual = NULL;
  individualsFactory* factory = NULL;
  i_objectiveFunction* objectiveFunction = NULL;
  i_selector* selector = NULL;
  i_distribution* distribution = NULL;

  vector<individual> individuals;
  vector<individual> offsprings;

  individual bestSolutionHolder;

  void findBestIndividual();
  void createOffspringPopulation();
  void mutateOldPopulation();
  void selectNewPopulation();

  double normalize(double target);
  void normalizePopulation(vector<individual>* population);

	double countAverageFitness();
	double countVariation();
	double countStandardDerivative();
};

#endif //GENEVANN_POPULATION_H
