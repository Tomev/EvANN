#ifndef GENEVANN_SWARM_H
#define GENEVANN_SWARM_H

#include "../NN/neuralNet.h"
#include "fireflyFactory.h"
#include "../ObjectiveFunctions/objectiveFunctions.h"

// TODO: constant correctness

class swarm
{

public:
	swarm(double* stepSize, double* baseAttraction, double* absorption,
				unsigned int size, i_distribution* distribution, neuralFireflyStrategy::topology* fireflyStructure,
				neuralNet* nn);

	void findSolution();

private:

	unsigned int iterations = 50000;

	vector<firefly> fireflies;
	firefly* bestFirefly;
	i_objectiveFunction* objectiveFunction = NULL;

};


#endif //GENEVANN_SWARM_H
