#include "neuron.h"

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