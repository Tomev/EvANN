#include <iostream>

#include "GA/population.h"
#include "NN/neuralNet.h"

#include "time.h"

struct testCase
{
  vector<double> input;
  vector<double> output;
};

using namespace std;

static void fillTestCases();
static void initializePopulation(population *p);
static void printOutputs(vector<double> *outputs);
static double countTotalError();

static exponentialDistribution distribution;

static vector<int> topology = {3, 3, 2};
static vector<double> input = {3.14, 12.0, 7.0};
static vector<double> output;
static vector<testCase> cases;

static neuralNet nn(&topology);

static int populationSize = 30;

// To pause console at some occasions.
string PAUSE;

int main()
{
  // Set random seed for proper functioning of GA.
  srand(time(NULL));

  // Fill test cases container
  fillTestCases();

  individual i(&topology, &distribution);

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

// Counts total error between test cases outputs and neural net outputs, for weights given
// by the individual and sets this error as evaluation value of individual.
static void rateIndividual(individual *i)
{
  // Set weights according to given individual.
  nn.setWeightsFromGASolution(i);

  // Count total error.
  double totalError = countTotalError();

  // Set total error as individuals fitness value
  i->setFitnessValue(totalError);
}

static double countTotalError()
{
  vector<testCase> cases;


}

static void getTestCases(vector<testCase> *cases)
{

}