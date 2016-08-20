#ifndef GENEVANN_NEURON_H
#define GENEVANN_NEURON_H

#include <vector>
#include <string>

#include "Activation Functions/sigmoidFunction.h"
#include "Activation Functions/linearFunction.h"

using namespace std;

class neuron;

struct neuronOutput
{
  neuronOutput(neuron *target)
  {
    this->target = target;
  }

  neuron *target;
  double weight;
};

typedef vector<neuron> layer;

class neuron {
public:
	neuron();

  double input;
  double baseOutput;
	double bias;

  void createNewConnection(neuron *target);
  void setOutputsWeightsAndBias(const vector<double> *weights);
  void resetInputValue();
	unsigned int getConnectionsNumber();

  void fire();

  string toString();

private:
	i_activationFunction *activationFunction;
	vector<neuronOutput> outputs;

};



#endif
