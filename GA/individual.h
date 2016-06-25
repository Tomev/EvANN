#ifndef GENEVANN_INDIVIDUAL_H
#define GENEVANN_INDIVIDUAL_H

#include <vector>
#include <string>
#include <math.h>

#include "exponentialDistribution.h"

using namespace std;

typedef vector<double> weights;
typedef vector<weights> neurons;
typedef vector<neurons> layers;

class individual {

public:
  individual(vector<int> *topology, i_distribution *distribution);

  void mutate();
  individual cross(individual *parent);

  string toString();

	void setEvaluationValue(double val);
	double getEvaluationValue();

protected:
  layers solution;

private:
  // TODO: Change to some kind of smart pointer.
  vector<int> *topology = NULL;

  double evaluationValue;

  // TODO: Change to some kind of smart pointer.
  i_distribution *distribution = NULL;

  // Biased and unbiased chromosome mutation probability. 10% is recommended.
  double chromosomeMutationProbabilityPercent = 10;
  // Number of nodes mutated during nodeMutation. Note that same node may be changed.
  // 2 is recommended.
  int numberOfNodesToMutate = 2;

  void unbiasedMutation();
  void biasedMutation();
  void nodeMutation();

  individual crossoverWeights(individual *parent);
  individual crossoverNodes(individual *parent);


  bool mutationOccurred();
};

#endif //GENEVANN_INDIVIDUAL_H