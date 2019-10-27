#ifndef GENEVANN_SWARM_H
#define GENEVANN_SWARM_H

#include "../NN/neuralNet.h"
#include "fireflyFactory.h"
#include "../ObjectiveFunctions/objectiveFunctions.h"
#include "../ObjectiveFunctions/Normalizers/i_normalizer.h"

class swarm
{

public:
	swarm( double *stepSize, double *baseAttraction, double *absorption,
	       unsigned int size, unsigned int iterations,
	       i_distribution *distribution, neuralNet* nn);

	void findSolution();
  void* getResult();

private:

	unsigned int iterations = 10000;

	vector<firefly> fireflies;
	firefly* bestFirefly = nullptr;
	i_objectiveFunction* objectiveFunction = nullptr;

	firefly bestSolutionHolder;
	void updateBestSolutionHolder(firefly* ff);
  void moveFFAndUpdateSwarmData(firefly* ff, firefly* target);

  firefly* findBrightestFirefly();

	double countFitnessSum();
	double countVariation();
	double countStandardDerivative();

};


#endif //GENEVANN_SWARM_H
