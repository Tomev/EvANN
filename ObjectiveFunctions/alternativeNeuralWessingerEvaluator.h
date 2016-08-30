#ifndef GENEVANN_ALTERNATIVENEURALWESSINGEREVALUATOR_H
#define GENEVANN_ALTERNATIVENEURALWESSINGEREVALUATOR_H

#include "i_objectiveFunction.h"
#include "../NN/neuralNet.h"

class alternativeNeuralWessingersEvaluator : public i_objectiveFunction
{
public:
	alternativeNeuralWessingersEvaluator(neuralNet* nn);

	double evaluate(void* solution);
	void printTestCases(void *solution);

private:
	neuralNet* nn;
	double calculateOutputValue(double input, double nnOutput);

	double trialFunctionValue(double t, double nnOutput);
	double trialFunctionDerivativeValue(double t, double nnOutput);
	double trialFunctionNNPartDerivativeValue(double t);
};

#endif //GENEVANN_ALTERNATIVENEURALWESSINGEREVALUATOR_H
