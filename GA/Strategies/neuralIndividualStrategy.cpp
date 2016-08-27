#include "neuralIndividualStrategy.h"

#include <iostream>
#include <cassert>

neuralIndividualStrategy::neuralIndividualStrategy
    (vector<unsigned int>* topology, i_distribution *distribution) :
    distribution(distribution)
{
  {
    // Check if topology was set. If not log error and die return;
    if(topology == NULL)
    {
      // TODO: Consider some kind of logger.
      cout << "\nERROR: Topology was not set!\n";
      return;
    }

    // Topology must be remembered for children generation.
    this->topology = topology;

    // Topology size is number of layers, and value of each element is number of neurons
    // on this layer. Solution can be constructed thanks to that information.
    // Note, that same topology is used to construct neural net. Solution doesn't have
    // output layer, hence -1 in first for.

    // Initialize solution

    // For each potential layer
    for(unsigned int l = 0; l < topology->size()-1; ++l)
    {
      // Add new layer to solution
      solution.push_back(layer());

      // For each potential neuron
      for(unsigned int n = 0; n < topology->at(l); ++n)
      {
        // Add new neuron (which is vector of weights) to solution
        solution.at(l).push_back(neuron());

        // For each potential weight + bias
        for(unsigned int w = 0; w < topology->at(l+1) + 1; ++w)
        {
          // Add new weight selected from given distribution to the vector
          solution.at(l).at(n).push_back(distribution->getRandomNumberFromDistribution());
        }
      }
    }
  }
}

void* neuralIndividualStrategy::getSolution()
{
  return &solution;
}

void neuralIndividualStrategy::setSolution(void *newSolution)
{
  /* As copying pointer won't do the trick each value in current
   * individuals solution vector is replaced by adequate value from
   * new solution. Note that size of new solution and current solution
   * are meant to be same. */

  vector<layer>* parent = (vector<layer>*) newSolution;

  assert(parent->size() == solution.size());

  // For each layer
  for(unsigned int l = 0; l < solution.size(); ++l)
  {
    assert(parent->at(l).size() == solution.at(l).size());

    // For each neuron on that layer
    for(unsigned int n = 0; n < solution.at(l).size(); ++n)
    {
      assert(parent->at(l).at(n).size() == solution.at(l).at(n).size());

      // For each weight of that neuron
      for(unsigned int w = 0; w < solution.at(l).at(n).size(); ++w)
      {
        // Replace solutions value at current weight
        solution.at(l).at(n).at(w) = parent->at(l).at(n).at(w);
      }
    }
  }
}

// Select mutation method(s) here. nodeMutation is preferred as it's the most effective one.
void neuralIndividualStrategy::mutate()
{
  nodeMutation();
}

// For each entry in the chromosome, this operator will with fixed probability
// replace it with a random value chosen from the initialization probability
// i_distribution.
void neuralIndividualStrategy::unbiasedMutation()
{
  // For each layer.
  for(unsigned int i = 0; i < solution.size(); ++i)
  {
    // For each neuron.
    for(unsigned int j = 0; j < solution.at(i).size(); ++j)
    {
      // For each weight.
      for(unsigned int k = 0; k < solution.at(i).at(j).size(); ++k)
      {
        // If mutation occurred select new weight value;
        if(hasMutationOccurred()) solution.at(i).at(j).at(k) =
                                      distribution->getRandomNumberFromDistribution();
      }
    }
  }
}

// For each entry in the chromosome, this operator will with fixed probability
// add to it a random value chosen from the initialization probability i_distribution.
void neuralIndividualStrategy::biasedMutation()
{
  // For each layer.
  for(unsigned int i = 0; i < solution.size(); ++i)
  {
    // For each neuron.
    for(unsigned int j = 0; j < solution.at(i).size(); ++j)
    {
      // For each weight.
      for(unsigned int k = 0; k < solution.at(i).at(j).size(); ++k)
      {
        // If mutation occurred select add random value from selected i_distribution
        // to current value;
        if(hasMutationOccurred()) solution.at(i).at(j).at(k) +=
                                      distribution->getRandomNumberFromDistribution();
      }
    }
  }
}

// This operator selects n non-input nodes of the network which the parent chromosome
// represents. For each of the ingoing links to these n nodes, the operator adds to
// the links weight a random value from the initialization probability i_distribution.
void neuralIndividualStrategy::nodeMutation()
{
  int layerNumber;
  int neuronNumber;

  // For each node to mutate.
  for(unsigned int i = 0; i < numberOfNodesToMutate; ++i)
  {
    // Select random layer and position in the layer.
    layerNumber   = rand() % solution.size();
    neuronNumber  = rand() % solution.at(layerNumber).size();

    // For each weight of selected neuron
    for(unsigned int j = 0; j < solution.at(layerNumber).at(neuronNumber).size(); ++j)
    {
      // Add pseudo-random number generated by selected i_distribution.
      solution.at(layerNumber).at(neuronNumber).at(j) +=
          distribution->getRandomNumberFromDistribution();
    }
  }
}

// Select crossing method(s) here.
// Note that there are small differences between the two.
// Check D. Montana's work for more info.
void neuralIndividualStrategy::cross(void *solution, void *target)
{
  crossoverWeights(solution, target);
}

// This operator puts a value into each position of the child's chromosome by
// randomly selecting one of the two parents and using the value in the same
// position on that parent's chromosome.
void neuralIndividualStrategy::crossoverWeights(void *solution, void *target)
{
  // Retype solution and target vectors
  vector<layer>* parent = (vector<layer>*) solution;
  vector<layer>* t = (vector<layer>*) target;

  /* Dominant parent is the one whose chromosome will be passed to offspring
   * Its selected randomly for each weight anew. */

  vector<layer>* dominantParent;

  assert(parent->size() == this->solution.size());

  // For each layer
  for(unsigned int l = 0; l < this->solution.size(); ++l)
  {
    assert(parent->at(l).size() == this->solution.at(l).size());

    // For each neuron in this layer
    for (unsigned int n = 0; n < this->solution.at(l).size(); ++n)
    {
      assert(parent->at(l).at(n).size() == this->solution.at(l).at(n).size());

      // Clear neuron weights layer;
      t->at(l).at(n).clear();

      // For each weight of that neuron
      for (unsigned int w = 0; w < this->solution.at(l).at(n).size(); ++w)
      {
        // Randomly select dominant parent
        dominantParent = (rand() % 2 == 0) ? &this->solution : parent;

        // Set child's trait on this position same to dominantParent.
        t->at(l).at(n).push_back(dominantParent->at(l).at(n).at(w));
      }
    }
  }
}

// For each node in the network encoded by the child chromosome, this operator
// selects one of the two parent's networks and finds the corresponding node in this
// network. It then puts the weight of each ingoing link to the parent's node into
// the corresponding link of the child's network.
void neuralIndividualStrategy::crossoverNodes(void *solution, void *target)
{
  // Retype solution and target vectors
  vector<layer>* parent = (vector<layer>*) solution;
  vector<layer>* t = (vector<layer>*) target;

  /* Dominant parent is the one whose chromosome will be passed to offspring
   * Its selected randomly for each weight anew. */

  vector<layer>* dominantParent;

  assert(parent->size() == this->solution.size());

  // For each layer
  for(unsigned int l = 0; l < this->solution.size(); ++l)
  {
    assert(parent->at(l).size() == this->solution.at(l).size());

    t->at(l).clear();

    // For each neuron in this layer
    for (unsigned int n = 0; n < this->solution.at(l).size(); ++n)
    {
      // Randomly select dominant parent
      dominantParent = (rand() % 2 == 0) ? &this->solution : parent;

      // Set child's trait on this position same to dominantParent.
      t->at(l).push_back(dominantParent->at(l).at(n));
    }
  }
}

// For debug purposes.
string neuralIndividualStrategy::toString()
{
  string result = "Solution: \n";

  for(unsigned int i = 0; i < solution.size(); ++i)
  {
    for (unsigned int j = 0; j < solution.at(i).size(); ++j)
    {
      result += "Layer " + to_string(i) + ", Neuron " + to_string(j) + ", Weights: ";

      for(unsigned int k = 0; k < solution.at(i).at(j).size(); ++k)
        result += to_string(solution.at(i).at(j).at(k)) + ", ";

      // Pop coma and space bar.
      result.pop_back();
      result.pop_back();

      result += "\n";
    }

    result += "\n";
  }

  return result;
}

bool neuralIndividualStrategy::hasMutationOccurred()
{
  return  (rand() % 100) < chromosomeMutationProbabilityPercent;
}