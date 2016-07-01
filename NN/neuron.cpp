#include "neuron.h"

#include <cassert>

neuron::neuron()
{
	activationFunction = new sigmoidFunction();
}

void neuron::fire()
{
	baseOutput = activationFunction->getOutput(input);

	// For each output
	for(int o = 0; o < outputs.size(); ++o)
		outputs.at(o).target->input += outputs.at(o).weight * baseOutput;
}

void neuron::resetInputValue()
{
	input = 0;
}

void neuron::setOutputsWeights(const vector<double> *weights)
{
	assert(weights->size() == outputs.size());

	// For each weight in given vector
	for(int w = 0; w < weights->size(); ++w)
	{
		// Set this weight as weight of w-th neurons output.
		outputs.at(w).weight = weights->at(w);
	}
}