#include <iostream>
#include <ctime>

#include "FA/swarm.h"
#include "GA/population.h"

using namespace std;

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
  Exit, OriginalWork, GANNWessingerDefault, FANNWessingerDefault, GANNWessinger, FANNWessinger
};

// Update each time changes in enum are made
static unsigned int maxInput = 5;

int main()
{
  exponentialDistribution distribution;
  neuralFireflyStrategy::topology topology = {1, 4, 1};
  neuralNet nn(&topology);
  alternativeNeuralWessingersEvaluator evaluator(&nn);

  unsigned int experimentsNum = 1;

  /* Setup */

  // Set random seed for proper functioning of randomizers.
  std::random_device rd;
  srand(rd());
  clock_t start;
  string PAUSE;

  /* Setup finished */

  // UI xD

  cout << "Select task to perform: " << endl;
  cout << "0) exit," << endl;
  cout << "1) check results from original work," << endl;
  cout << "2) train NN using EA and default settings to solve Wessinger's equation," << endl;
  cout << "3) train NN using FA and default settings to solve Wessinger's equation," << endl;
  cout << "4) train NN using EA to solve Wessinger's equation," << endl;
  cout << "5) train NN using FA to solve Wessinger's equation." << endl;
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

      // Set attributes
      // TR TODO: Add validations

      cout << "Enter population size:" << endl << ">";
      cin >> swarmSize;

      cout << "Enter iterations number:" << endl << ">";
      cin >> iterations;

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

      // TR TODO: Validators needed.

      cout << "Enter population size:" << endl << ">";
      cin >> swarmSize;

      cout << "Enter iterations number:" << endl << ">";
      cin >> iterations;

      cout << "Enter step size:" << endl << ">";
      cin >> stepSize;

      cout << "Enter base attraction:" << endl << ">";
      cin >> baseAttraction;

      cout << "Enter absorption:" << endl << ">";
      cin >> baseAttraction;

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

      case FANNWessingerDefault:
      // FIREFLY ALGORITHM WITH EVALUATION WITH DEFAULT SETTINGS

        cout << "Using FF with default settings." << endl;

        for(unsigned int i = 0; i < experimentsNum; ++i) {

          cout << "Iteration " << i << endl;

          swarmSize = 50;
          iterations = 700;
          baseAttraction = 0.5;
          stepSize = 0.01;
          absorption = 1.0;

            // Start timer
          start = clock();

          s = new swarm(&stepSize, &baseAttraction, &absorption, swarmSize,
                        iterations, &distribution, &nn);

          s->findSolution();

          nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer>*)s->getResult());
          //nn.print();

          evaluator.printTestCases(s->getResult());

          // Get time
          cout << "Elapsed time: " << double(clock() - start) / CLOCKS_PER_SEC << " s.\n\n";
        }
    break;
    // FIREFLY ALGORITHM WITH EVALUATION WITH DEFAULT SETTINGS
    case GANNWessingerDefault:
    // GENETIC ALGORITHM WITH EVALUATION WITH DEFAULT SETTINGS

      cout << "Using EA with default settings." << endl;

      for(unsigned int i = 0; i < experimentsNum; ++i) {

        cout << "Iteration " << i << endl;

        // Set attributes
        swarmSize = 50;
        iterations = 7000;

        // Start timer
        start = clock();

        p = new population(swarmSize, iterations, &nn, &distribution);

        p->findSolution();

        nn.setWeightsFromNeuronsStructure((vector<neuralFireflyStrategy::layer> *) p->getResult());
        //nn.print();

        evaluator.printTestCases(p->getResult());

        // Get time
        cout << "Elapsed time: " << double(clock() - start) / CLOCKS_PER_SEC << " s.\n\n";
      }

    // GENETIC ALGORITHM WITH EVALUATION WITH DEFAULT SETTINGS
    break;
    case Exit:
    default:
      return EXIT_SUCCESS;
  }

  cout << endl;

  // Pause before exit
  //system("pause");
  return EXIT_SUCCESS;
}