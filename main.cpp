#include <iostream>

#include "Distributions/distributions.h"
#include "FA/swarm.h"
#include "GA/population.h"

#include "time.h"

using namespace std;


static exponentialDistribution distribution;

static neuralFireflyStrategy::topology topology = {1, 4, 1};
static vector<double> output;

static neuralNet nn(&topology);
static neuralWessingerEvaluator evaluator(&nn);

static double stepSize = 0.01;
static double baseAttraction = 1;
static double absorption = 1.0;
static unsigned int swarmSize = 50;

// To pause console at some occasions.
string PAUSE;

int main()
{
  /* Setup */

  // Set random seed for proper functioning of randomizers.
  srand(time(NULL));

  /* Setup finished */

  // FIREFLY ALGORITHM WITH EVALUATION

  /*
  swarm s(&stepSize, &baseAttraction, &absorption, swarmSize,
          &distribution, &topology, &nn);

  s.findSolution();

  nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer>*)s.getResult());
  nn.print();

  evaluator.printTestCases(s.getResult());
  */

  // FIREFLY ALGORITHM WITH EVALUATION

  // GENERIC ALGORITHM WITH EVALUATION




  // GENETIC ALGORITHM WITH EVALUATION

	//cin >> PAUSE;
  return EXIT_SUCCESS;
}


// For debug purposes. Used to print vector of doubles (eg. neural net output).
static void printVector(vector<double> *v)
{
  cout << "Outputs: " << endl;

  // For each value
  for(int o = 0; o < v->size(); ++o)
  {
    // Print it
    cout << to_string(v->at(o)) << endl;
  }
}