#ifndef GENEVANN_FIREFLYFACTORY_H
#define GENEVANN_FIREFLYFACTORY_H

#include "Strategies/strategies.h"
#include "firefly.h"

class fireflyFactory {
public:

	enum strategiesType
	{
		neuralFirefly
	};

	fireflyFactory(double *stepSize, double *baseAttraction, double *absorption,
	               i_distribution *distribution, void* fireflyStructure);

	fireflyFactory(double *stepSize, double *baseAttraction, double *absorption,
	               i_distribution *distribution, neuralFireflyStrategy::topology* fireflyStructure);

	firefly createFirefly();

private:
	unsigned int strategyType;

	double* stepSize;
	double*	baseAttraction;
	double* absorption;

	i_distribution* distribution;
	void* fireflyStructure;

	firefly createNeuralFirefly();

};


#endif //GENEVANN_FIREFLYFACTORY_H
