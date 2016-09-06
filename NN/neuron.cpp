#include "neuron.h"

#include <cassert>
#include <iostream>

neuron::neuron()
{
	activationFunction = new sigmoidFunction();
}

neuron::neuron(i_activationFunction* function)
{
  this->activationFunction = function;
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
  assert(weights->size() == outputs.size()+1);

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
  input = bias;
}

void neuron::fire()
{
	double baseOutput = activationFunction->getOutput(input);

	// For each output
	for(int o = 0; o < outputs.size(); ++o)
		outputs.at(o).target->input += outputs.at(o).weight * baseOutput;
}

double neuron::getBiasValue()
{
	return bias;
}

double neuron::getIthOutputWeight(unsigned int i)
{
	return outputs.at(i).weight;
}

double neuron::getOutput()
{
	return input;
}

// TODO: For debugging purposes.
string neuron::toString()
{
  string result = "Weights: ";

  for(int w = 0; w < outputs.size(); ++w)
  {
    result += to_string(outputs.at(w).weight) + ", ";
  }

  // Pop coma and space bar.
  result.pop_back();
  result.pop_back();

  result += " Bias: " + to_string(bias) + "\n";

  return result;
}

void neuron::print()
{
  cout << this->toString() << endl;
}