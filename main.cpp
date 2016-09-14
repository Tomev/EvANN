#include <iostream>
#include <ctime>

#include "FA/swarm.h"
#include "GA/population.h"


using namespace std;


static exponentialDistribution distribution;

static neuralFireflyStrategy::topology topology = {1, 4, 1};

static neuralNet nn(&topology);
static alternativeNeuralWessingersEvaluator evaluator(&nn);

static double stepSize = 0.01;
static double baseAttraction = 0.5;
static double absorption = 1.0;
static unsigned int swarmSize = 50;
static unsigned int iterations = 700;
static unsigned int taskID = 0;

static vector<neuralFireflyStrategy::layer> solution;
static population* p;
static swarm* s;

enum tasksID
{
  Exit, OriginalWork, GANNWessinger, FANNWessinger
};

// Update each time changes in enum are made
static unsigned int maxInput = 3;

int main()
{
  /* Setup */

  // Set random seed for proper functioning of randomizers.
  srand(time(NULL));
  clock_t start;

  /* Setup finished */

  // UI xD

  cout << "Select task to perform: " << endl;
  cout << "0) exit," << endl;
  cout << "1) check results from original work," << endl;
  cout << "2) train NN using EA to solve Wessinger's equation," << endl;
  cout << "3) train NN using FA to solve Wessinger's equation." << endl;
  cout << "> ";


  cin >> taskID;


  while(cin.fail() || taskID > maxInput)
  {
    cout << "Incorrect input. Please enter correct one." << endl;
    cout << "> ";
    cin >> taskID;
  }

  switch(taskID)
  {
    case OriginalWork:
      // NEURAL NET TEST WITH FIXED PARAMETERS WITH EVALUATION

			solution = {
					{{-1.552, -0.4596, -1.9932, -1.1452, 0.0}},
					{{0.2565, -1.8594}, {0.4425, -2.4258}, {0.0024, -1.0052}, {0.5258, -1.5866}}
			};

			nn.setWeightsFromNeuronsStructure(&solution);
			nn.print();

			cout << "Error: " << evaluator.evaluate(&solution) << endl << endl;

			evaluator.printTestCases(&solution);

      // NEURAL NET TEST WITH FIXED PARAMETERS WITH EVALUATION
      break;
    case GANNWessinger:
      // GENERIC ALGORITHM WITH EVALUATION

      // Start timer
      start = clock();

			p = new population(swarmSize, iterations, &nn, &distribution);

			p->findSolution();

			nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer>*)p->getResult());
			nn.print();

			evaluator.printTestCases(p->getResult());

      // Get time
      cout << "Elapsed time: " << double(clock() - start) / CLOCKS_PER_SEC << " s." << endl;

      // GENETIC ALGORITHM WITH EVALUATION
      break;
    case FANNWessinger:
      // FIREFLY ALGORITHM WITH EVALUATION

      // Start timer
      start = clock();

			s = new swarm(&stepSize, &baseAttraction, &absorption, swarmSize,
										iterations, &distribution, &nn);

			s->findSolution();

			nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer>*)s->getResult());
			nn.print();

			evaluator.printTestCases(s->getResult());

      // Get time
      cout << "Elapsed time: " << double(clock() - start) / CLOCKS_PER_SEC << " s." << endl;

      // FIREFLY ALGORITHM WITH EVALUATION
      break;

    case Exit:
    default:
      return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}