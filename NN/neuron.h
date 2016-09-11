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
  neuron(i_activationFunction* function);

  double input;

  void createNewConnection(neuron *target);
  void setOutputsWeightsAndBias(const vector<double> *weights);
  void resetInputValue();
	unsigned int getConnectionsNumber();

	double getBiasValue();
	double getIthOutputWeight(unsigned int i);
	double getOutput();

  void fire(bool isInputLayer);

  string toString();
  void print();

private:
	i_activationFunction *activationFunction;
	vector<neuronOutput> outputs;

  double bias = 0;

};



#endif
