#include <iostream>

#include "FA/swarm.h"
#include "GA/population.h"
#include "NN/neuralNet.h"

#include "time.h"

#include "FA/Strategies/neuralFireflyStrategy.h"
#include "FA/firefly.h"

struct testCase
{
  vector<double> input;
  vector<double> output;
};

using namespace std;


static void printOutputs(vector<double> *outputs);

static exponentialDistribution distribution;

static vector<unsigned int> topology = {3, 3, 2};
static vector<double> input = {3.14, 12.0, 7.0};
static vector<double> output;
static vector<testCase> cases;

static population p;
static neuralNet nn(&topology);

typedef double weight;
typedef vector<weight> n; // Simplified
typedef vector<n> l;

// To pause console at some occasions.
string PAUSE;

int main()
{
  /* Setup */

  // Set random seed for proper functioning of randomizers.
  srand(time(NULL));

  /* Setup finished */

	double stepSize = 0.1, baseAttraction = 0.5, absorption = 5.0;

	firefly f1(new neuralFireflyStrategy(&stepSize, &baseAttraction, &absorption, &distribution, &topology));
	firefly f2(new neuralFireflyStrategy(&stepSize, &baseAttraction, &absorption, &distribution, &topology));
	f1.initialize();
	f2.initialize();

	f1.print();

	f1.flyTowards(f2.getSolution());

	f1.print();

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