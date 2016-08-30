#ifndef GENEVANN_SWARM_H
#define GENEVANN_SWARM_H

#include "../NN/neuralNet.h"
#include "fireflyFactory.h"
#include "../ObjectiveFunctions/objectiveFunctions.h"

// TODO: constant correctness

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
  double highestKnownError = 0.0;

	vector<firefly> fireflies;
	firefly* bestFirefly = NULL;
	i_objectiveFunction* objectiveFunction = NULL;

	firefly bestSolutionHolder;

  firefly* findBrightestFirefly();
  double normalize(double value);
  void normalizeSwarm();

};


#endif //GENEVANN_SWARM_H
