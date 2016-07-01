#ifndef GENEVANN_NEURALNET_H
#define GENEVANN_NEURALNET_H

#include "neuron.h"
#include "../GA/individual.h"

class neuralNet {
public:
  neuralNet(const vector<int> topology);

	void setInputsValue(const vector<double> *inputs);
	void setWeightsFromGASolution(const individual *i);
	void feedForward();
	void resetNonInputLayerInputs();
  void getResults(vector<double> *results);

protected:

private:
  vector<layer> net;

  void setNeuronConnections();
};

#endif //GENEVANN_NEURALNET_H
