#ifndef GENEVANN_NEURALNET_H
#define GENEVANN_NEURALNET_H

#include "neuron.h"

class neuralNet {
public:
  neuralNet(const vector<int> topology);

  void feedForward();

  void getResults(vector<double> *results);

  void setInputsValue(const vector<double> *inputs);

protected:

private:
  vector<layer> net;

  void setNeuronConnections();
};

#endif //GENEVANN_NEURALNET_H
