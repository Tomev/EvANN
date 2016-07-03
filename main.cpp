#include <iostream>

#include "GA/population.h"
#include "NN/neuralNet.h"

#include "time.h"

using namespace std;

static void initializePopulation(population *p);
static void printOutputs(vector<double> *outputs);

static exponentialDistribution distribution;

static vector<int> topology = {3, 3, 2};
static vector<double> input = {3.14, 12.0, 7.0};
static vector<double> output;

static int populationSize = 30;

// To pause console at some occasions.
string PAUSE;

int main()
{
  // Set random seed for proper functioning of GA.
  srand(time(NULL));

  individual i(&topology, &distribution);
  neuralNet nn(&topology);

  cout << i.toString();

  nn.setInputsValue(&input);
  nn.setWeightsFromGASolution(&i);
  nn.feedForward();
  nn.getResults(&output);

  //cout << nn.toString();

  printOutputs(&output);

	//cin >> PAUSE;
  return EXIT_SUCCESS;
}

static void initializePopulation(population *p)
{
  // For each potential individual.
  for(int i = 0; i < populationSize; ++i)
  {
    p->addIndividual(&topology, &distribution);
  }
}

static void printOutputs(vector<double> *outputs)
{
  cout << "Outputs: " << endl;

  // For each output
  for(int o = 0; o < outputs->size(); ++o)
  {
    cout << to_string(outputs->at(o)) << endl;
  }
}


