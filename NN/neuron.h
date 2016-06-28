#ifndef GENEVANN_NEURON_H
#define GENEVANN_NEURON_H

#include <vector>

using namespace std;

class neuron {
public:

  double baseOutput;
  double input;

  struct neuronOutput
  {
    neuronOutput(neuron *target)
    {
      this->target = target;
    }

    neuron *target;
    double exit;
  };

  void setOutputsWeights();
  void resetBaseOutput();

  vector<neuronOutput> outputs;
private:

};

typedef vector<neuron> layer;

#endif
