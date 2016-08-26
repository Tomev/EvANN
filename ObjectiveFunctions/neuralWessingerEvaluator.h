#ifndef GENEVANN_NEURALFIREFLYEVALUATOR_H
#define GENEVANN_NEURALFIREFLYEVALUATOR_H

#include "i_objectiveFunction.h"
#include "../FA/Strategies/neuralFireflyStrategy.h"
#include "../NN/neuralNet.h"

class neuralWessingerEvaluator : public i_objectiveFunction
{
public:

	neuralWessingerEvaluator(neuralNet* nn);

	double evaluate(void* solution);
	void printTestCases(void *solution);

private:
	neuralNet* nn;
	double calculateOutputValue(double input, double nnOutput);
};


#endif //GENEVANN_NEURALFIREFLYEVALUATOR_H
