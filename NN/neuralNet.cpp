#include "neuralNet.h"

#include <cassert>

// Creates neural net from given topology. Neurons connections are set, but all connections weights
// are null.
neuralNet::neuralNet(const vector<int> topology)
{
  // For each layer in topology
  for(int l = 0; l < topology.size(); ++l)
  {
    // Add layer
    net.push_back(layer());

    // For each neuron at current layer
    for(int n = 0; n < topology.at(l); ++n)
    {
      net.at(l).push_back(neuron());
    }
  }

  setNeuronConnections();
}

// Setting connections so that each neuron in each non-output layer targets each neuron of the next
// layer. Weights of the connections aren't set here.
void neuralNet::setNeuronConnections()
{
  // For each non-output layer
  for(int l = 0; l < net.size()-1; ++l)
  {
    // For each neuron in layer
    for(int n = 0; n < net.at(l).size(); ++n)
    {
      //For each neuron of next layer
      for(int nn = 0; n < net.at(l+1).size(); ++nn)
      {
        // Add to neuron at n output targeting nn
        neuron *target = &net.at(l+1).at(nn);
        net.at(l).at(n).outputs.push_back(neuronOutput(target));
      }
    }
  }
}

// Set inputs given by vector of values.
void neuralNet::setInputsValue(const vector<double> *inputs)
{
  assert(inputs != NULL);
  assert(inputs->size() == net.at(0).size());


  for(int i = 0; i < inputs->size(); ++i)
    net.at(0).at(i).input = inputs->at(i);
}

// Processes input data into output data.
void neuralNet::feedForward()
{
  // Reset input values
  resetNonInputLayerInputs();

  // For each layer starting at input layer
  for(int l = 0; l < net.size(); ++l)
  {
    // For each neuron in this layer
    for(int n = 0; n < net.at(l).size(); ++n)
    {
      // Fire each neuron
      net.at(l).at(n).fire();
    }
  }
}

// Used to ensure that inputs are reset when using same nn with different weights.
void neuralNet::resetNonInputLayerInputs()
{
  // For each non input layer
  for(int l = 1; l < net.size(); ++l)
  {
    // For each neuron
    for(int n = 0; n < net.at(l).size(); ++n)
    {
      // Reset neuron's input value.
      net.at(l).at(n).resetInputValue();
    }
  }
}

// Fills result container with neuron values from output layer.
void neuralNet::getResults(vector<double> *results)
{
  assert(results != NULL);

  // Clear result container
  results->clear();

  // For each neuron at output layer
  int outLayerIdx = net.size()-1;

  for(int n = 0; n < net.at(outLayerIdx).size(); ++n)
  {
    // Add output value to container.
    results->push_back(net.at(outLayerIdx).at(n).baseOutput);
  }
}

void neuralNet::setWeightsFromGASolution(const individual *i)
{
  assert(i->solution.size() == net.size()-1);

  // For each non-output layer of nn
  for(int l = 0; l < net.size()-1; ++l)
  {
    assert(i->solution.at(l).size() == net.at(l).size());

    // For each neuron in that layer
    for(int n = 0; n < net.at(l).size(); ++n)
    {
      assert(i->solution.at(l).at(n).size() == net.at(l).at(n).size());

      net.at(l).at(n).setOutputsWeights(i->solution.at(l).at(n));
    }
  }
}