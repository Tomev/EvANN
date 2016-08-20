#include "neuron.h"

#include <cassert>

neuron::neuron()
{
	activationFunction = new sigmoidFunction();
}

void neuron::createNewConnection(neuron *target)
{
  outputs.push_back(neuronOutput(target));
}

unsigned int neuron::getConnectionsNumber()
{
  return outputs.size();
}

void neuron::setOutputsWeightsAndBias(const vector<double> *weights)
{
	// -1 for bias
  assert(weights->size() == outputs.size()-1);

  // For each weight in given vector excluding last one (which is bias)
  for(int w = 0; w < weights->size() - 1; ++w)
  {
    // Set this weight as weight of w-th neurons output.
    outputs.at(w).weight = weights->at(w);
  }

	// Set bias
	bias = weights->at(weights->size()-1);
}

void neuron::resetInputValue()
{
  input = 0;
}

void neuron::fire()
{
	baseOutput = activationFunction->getOutput(input + bias);

	// For each output
	for(int o = 0; o < outputs.size(); ++o)
		outputs.at(o).target->input += outputs.at(o).weight * baseOutput;
}

// TODO: For debugging purposes.
string neuron::toString()
{
  string result = "";

  return result;
}