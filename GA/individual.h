#ifndef GENEVANN_INDIVIDUAL_H
#define GENEVANN_INDIVIDUAL_H

#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef vector<double> weights;
typedef vector<weights> neurons;
typedef vector<neurons> layers;

class individual {

public:
  individual(vector<int> *topology);

  void initialize();
  void mutate();

  individual cross(const individual parent);
	string toString();

	void setEvaluationValue(double val);
	double getEvaluationValue();

protected:
  layers solution;
  vector<int> *topology = NULL;

	double evaluationValue;

	// Used as argument in random number generation in exponential distribution.
	double lambda = 1;

  // Biased and unbiased chromosome mutation probability. 0.1 is recommended.
  double chromosomeMutationProbabilityPercent = 10;
  // Number of nodes mutated during nodeMutation. Note that same node may be changed.
  // 2 is recommended.
  int numberOfNodesToMutate = 2;

  void unbiasedMutation();
  void biasedMutation();
  void nodeMutation();

  double randomlyTurnNegative(double n);
  bool mutationOccurred();

};

#endif //GENEVANN_INDIVIDUAL_H