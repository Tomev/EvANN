#ifndef GENEVANN_NEURALINDIVIDUALSTRATEGY_H
#define GENEVANN_NEURALINDIVIDUALSTRATEGY_H

#include <vector>
#include <string>
#include <math.h>

#include "../../Distributions/exponentialDistribution.h"
#include "i_strategy.h"

using namespace std;

class neuralIndividualStrategy : public i_strategy
{
public:
  typedef vector<double> neuron;
  typedef vector<neuron> layer;

  neuralIndividualStrategy(vector<unsigned int>* topology, i_distribution *distribution);

  void* getSolution();
  void setSolution(void* newSolution);

  void cross(void* solution, void* target);
  void mutate();

  string toString();

private:
  vector<unsigned int> *topology = NULL;
  vector<layer> solution;

  //TR TODO: Change to some kind of smart pointer
  i_distribution* distribution;

  // Biased and unbiased chromosome mutation probability. 10% is recommended.
  double chromosomeMutationProbabilityPercent = 10;
  /* Number of nodes mutated during nodeMutation. Note that same node may be changed.
   * 2 is recommended. */
  int numberOfNodesToMutate = 2;

  void unbiasedMutation();
  void biasedMutation();
  void nodeMutation();

  void crossoverWeights(void* solution, void* target);
  void crossoverNodes(void* solution, void* target);

  bool hasMutationOccurred();
};


#endif //GENEVANN_NEURALINDIVIDUALSTRATEGY_H
