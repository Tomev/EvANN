#include "individual.h"
#include "exponentialDistribution.h"

#include <iostream>
#include <random>

// Initializing solution vectors with pseudo-random values with selected i_distribution.
// Note that solution is one layer smaller than neural net (solution doesn't have output
// layer, as it doesn't have weights."
individual::individual(vector<int> *topology, i_distribution *distribution)
{
  // Check if topology was set. If not log error and die return;
  if(topology == NULL)
  {
    // TODO: Consider some kind of logger.
    cout << "\nERROR: Topology was not set!\n";
    return;
  }

  this->distribution = distribution;

  // Topology must be remembered for children generation.
  this->topology = topology;

  // Topology size is number of layers, and value of each element is number of neurons
  // on this layer. Solution can be constructed thanks to that information.
  // Note, that same topology is used to construct neural net. Solution doesn't have
  // output layer, hence -1 in first for.
  for(unsigned int i = 0; i < topology->size()-1; ++i)
  {
    solution.push_back(neurons());

    for(unsigned int j = 0; j < topology->at(i); ++j)
    {
      solution.at(i).push_back(weights());

      for(unsigned int k = 0; k < topology->at(i+1); ++k)
        solution.at(i).at(j).push_back(distribution->getRandomNumberFromDistribution());
    }

  }
}

// Select mutation method(s) here.
// nodeMutation is preferred as it's the most effective one.
void individual::mutate()
{
  nodeMutation();
}

// For each entry in the chromosome, this operator will with fixed probability
// replace it with a random value chosen from the initialization probability
// i_distribution.
void individual::unbiasedMutation()
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
        if(mutationOccurred()) solution.at(i).at(j).at(k) =
                                       distribution->getRandomNumberFromDistribution();
      }
    }
  }
}

// For each entry in the chromosome, this operator will with fixed probability
// add to it a random value chosen from the initialization probability i_distribution.
void individual::biasedMutation()
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
        if(mutationOccurred()) solution.at(i).at(j).at(k) +=
                                       distribution->getRandomNumberFromDistribution();
      }
    }
  }
}

// This operator selects n non-input nodes of the network which the parent chromosome
// represents. For each of the ingoing links to these n nodes, the operator adds to
// the links weight a random value from the initialization probability i_distribution.
void individual::nodeMutation()
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

// Select crossing metohd(s) here.
// Note that there are small differences between the two.
// Check D. Montana's work for more info.
individual individual::cross(individual *parent)
{
  return crossoverWeights(parent);
}

// This operator puts a value into each position of the child's chromosome by
// randomly selecting one of the two parents and using the value in the same
// position on that parent's chromosome.
individual individual::crossoverWeights(individual *parent)
{
  individual child(topology, distribution);

  // Dominant parent is one who's trait will be passed to offspring. It will be
  // selected on random for each trait.
  individual *dominantParent;

  // For each layer
  for(unsigned int i = 0; i < solution.size(); ++i)
  {
    // For each neuron in this layer
    for(unsigned int j = 0; j < solution.at(i).size(); ++j)
    {
      // Clear neuron weights layer;
      child.solution.at(i).at(j).clear();

      // For each weight of that neuron
      for(unsigned int k = 0; k < solution.at(i).at(j).size(); ++k)
      {
        // Randomly select dominant parent
        dominantParent = (rand() % 2 == 0) ? this : parent;

        // Set child's trait on this position same to dominantParent.
        child.solution.at(i).at(j).push_back(dominantParent->solution.at(i).at(j).at(k));
      }
    }
  }

  return child;
}

// For each node in the network encoded by the child chromosome, this operator
// selects one of the two parent's networks and finds the corresponding node in this
// network. It then puts the weight of each ingoing link to the parent's node into
// the corresponding link of the child's network.
individual individual::crossoverNodes(individual *parent)
{
  individual child(topology, distribution);

  // Dominant parent is one who's trait will be passed to offspring. It will be
  // selected on random for each trait.
  individual *dominantParent;

  // For each layer
  for(unsigned int i = 0; i < solution.size(); ++i)
  {
    // Clear layer's neurons.
    child.solution.at(i).clear();

    // For each neuron in solution
    for(unsigned int j = 0; j < solution.at(i).size(); ++j)
    {
      // Randomly select dominant parent
      dominantParent = (rand() % 2 == 0) ? this : parent;

      // Set child's trait on this position same to dominantParent.
      child.solution.at(i).push_back(dominantParent->solution.at(i).at(j));
    }
  }

  return child;
}

void individual::setEvaluationValue(const double val)
{
	evaluationValue = val;
}

double individual::getEvaluationValue()
{
  return evaluationValue;
}

// For debug purposes.
string individual::toString()
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

bool individual::mutationOccurred()
{
  return  (rand() % 100) < chromosomeMutationProbabilityPercent;
}