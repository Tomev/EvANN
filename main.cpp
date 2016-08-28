#include <iostream>

#include "Distributions/distributions.h"

#include "FA/swarm.h"
#include "GA/population.h"

#include "time.h"
#include "GA/Strategies/neuralIndividualStrategy.h"

using namespace std;


static exponentialDistribution distribution;

static neuralFireflyStrategy::topology topology = {1, 4, 1};

static neuralNet nn(&topology);
static neuralWessingerEvaluator evaluator(&nn);

static double stepSize = 0.01;
static double baseAttraction = 1;
static double absorption = 1.0;
static unsigned int swarmSize = 50;

// To pause console at some occasions.
// string PAUSE;

int main()
{
  /* Setup */

  // Set random seed for proper functioning of randomizers.
  srand(time(NULL));

  /* Setup finished */

  // FIREFLY ALGORITHM WITH EVALUATION
  /*
  swarm s(&stepSize, &baseAttraction, &absorption, swarmSize,
          &distribution, &nn);

  s.findSolution();

  nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer>*)s.getResult());
  nn.print();

  evaluator.printTestCases(s.getResult());
  */
  // FIREFLY ALGORITHM WITH EVALUATION

  // GENERIC ALGORITHM WITH EVALUATION

  population p(swarmSize, &nn, &distribution);

  p.findSolution();

  nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer>*)p.getResult());
  nn.print();

  evaluator.printTestCases(p.getResult());

  // GENETIC ALGORITHM WITH EVALUATION

  // NEURAL NET TEST WITH FIXED PARAMETERS WITH EVALUATION
  /*
  vector<neuralFireflyStrategy::layer> solution = {
      {{-1.1552, -0.4596, -1.9932, -1.1452, 0.0}},
      {{0.2565, -1.8594}, {0.4425, -2.4258}, {0.0024, -1.0052}, {0.5258, -1.5826}}
  };

  nn.setWeightsFromNeuronsStructure(&solution);
  nn.print();

  cout << "Error: " << evaluator.evaluate(&solution) << endl << endl;

  evaluator.printTestCases(&solution);

   */
  // NEURAL NET TEST WITH FIXED PARAMETERS WITH EVALUATION


	//cin >> PAUSE;
  return EXIT_SUCCESS;
}