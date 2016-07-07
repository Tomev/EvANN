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
static void rateIndividual(individual *i);
static double countTotalError();
static void rememberBestSolution(population *p);
static void selectParents(individual *p1, individual *p2);

static void printOutputs(vector<double> *outputs);

static exponentialDistribution distribution;

static vector<int> topology = {3, 3, 2};
static vector<double> input = {3.14, 12.0, 7.0};
static vector<double> output;
static vector<testCase> cases;

static population p;
static neuralNet nn(&topology);

static int populationSize = 50;
static int iterationsNumber = 50000;
static int offspringNumber = 10;

static individual bestSolution;

// To pause console at some occasions.
string PAUSE;

int main()
{
  /* Setup */

  // Set random seed for proper functioning of GA.
  srand(time(NULL));

  // Fill test cases container
  fillTestCases();

  /* Setup finished */

  individual i(&topology, &distribution);

  cout << i.toString();

  nn.setInputsValue(&input);
  nn.setWeightsFromGASolution(&i);
  nn.feedForward();
  nn.getResults(&output);

  //cout << nn.toString();

  printOutputs(&output);





  /* Finding optimal weights */

  // Initialize population
  initializePopulation(&p);
  // For each individual in population
  for(int i = 0; i < populationSize; ++i)
  {
    // Evaluate individual
    individual *currentIndividual = &(p.individuals.at(i));
    currentIndividual->.setFitnessValue(rateIndividual(currentIndividual));
  }
  // Normalize populations evaluation
  p.normalizeFitnesses();
  // For given number of iterations or until optimal solution is found
  for(int i = 0; i < iterationsNumber; ++i)
  {
    // Remember best solution
    rememberBestSolution(&p);
    // For given number of offsprings
    for(int o = 0; o < offspringNumber; ++o)
    {
      // Select parents
      individual *parent1;
      individual *parent2;

      selectParents(parent1, parent2);
      // Create offspring and add it to population
      p.addIndividual(parent1->cross(parent2));
    }
    // For each individual in population
      // Apply mutators
      // Evaluate individual
    //
  }
  /* Optimal weights found */

  /* Applying optimal solution to problem */

  // Apply best individual to nn.
  nn.setWeightsFromGASolution(&bestSolution);

  // TODO

  // Print results

  /* Optimal solution applied */


	//cin >> PAUSE;
  return EXIT_SUCCESS;
}

// Filling test cases from given file.
void fillTestCases()
{

}

// Initialize given population.
static void initializePopulation(population *p)
{
  // For each potential individual.
  for(int i = 0; i < populationSize; ++i)
  {
    // Add new individual to the population.
    p->addIndividual(&topology, &distribution);
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



static double countTotalError()
{
  vector<testCase> cases;


}