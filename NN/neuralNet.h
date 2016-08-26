#ifndef GENEVANN_NEURALNET_H
#define GENEVANN_NEURALNET_H

#include "neuron.h"
#include "../FA/Strategies/neuralFireflyStrategy.h"

// TODO: constant correctness

class neuralNet {
public:
  neuralNet(const vector<unsigned int> *topology);

	void setInputsValue(const vector<double> *inputs);
	void setWeightsFromNeuronsStructure(const vector<neuralFireflyStrategy::layer>* solution);
	void feedForward();
	void resetNonInputLayerInputs();
  void getResults(vector<double> *results);

	string toString();
  void print();

protected:

private:
  vector<layer> net;

  void setNeuronConnections();
};

#endif //GENEVANN_NEURALNET_H
