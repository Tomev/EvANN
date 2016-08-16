#include <iostream>

#include "FA/swarm.h"
#include "GA/population.h"

#include "time.h"


struct testCase
{
  vector<double> input;
  vector<double> output;
};

using namespace std;


static void printOutputs(vector<double> *outputs);

static exponentialDistribution distribution;

static neuralFireflyStrategy::topology topology = {3, 3, 2};
static vector<double> input = {3.14, 12.0, 7.0};
static vector<double> output;
static vector<testCase> cases;

static neuralNet nn(&topology);

static double stepSize = 0.1;
static double baseAttraction = 0.5;
static double absorption = 5.0;

// To pause console at some occasions.
string PAUSE;

int main()
{
  /* Setup */

  // Set random seed for proper functioning of randomizers.
  srand(time(NULL));

  /* Setup finished */


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