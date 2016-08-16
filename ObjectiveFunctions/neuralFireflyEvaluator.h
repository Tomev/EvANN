#ifndef GENEVANN_NEURALFIREFLYEVALUATOR_H
#define GENEVANN_NEURALFIREFLYEVALUATOR_H

#include "i_objectiveFunction.h"
#include "../FA/Strategies/neuralFireflyStrategy.h"
#include "../NN/neuralNet.h"

class neuralFireflyEvaluator : public i_objectiveFunction
{
public:

	neuralFireflyEvaluator(neuralNet* nn);

	double evaluate(void* solution);

private:
	neuralNet* nn;
};


#endif //GENEVANN_NEURALFIREFLYEVALUATOR_H
