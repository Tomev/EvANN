#ifndef GENEVANN_NEURON_H
#define GENEVANN_NEURON_H

#include <vector>
#include "sigmoidFunction.h" // An alternative could be tanh.

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

  void setOutputsWeights();
  void resetBaseOutput();

  void fire();

  vector<neuronOutput> outputs;
private:
	i_activationFunction *activationFunction;

};



#endif
