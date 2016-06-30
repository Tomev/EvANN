#include <iostream>

#include "GA/population.h"
#include "time.h"

using namespace std;

exponentialDistribution distribution;

vector<int> topology = {3, 3, 2};
int populationSize = 30;

// To pause console at some occasions.
string PAUSE;

int main()
{
  // Set random seed for proper functioning of GA.
  srand(time(NULL));




	//cin >> PAUSE;
  return EXIT_SUCCESS;
}

void initializePopulation(population *p)
{
  // For each potential individual.
  for(int i = 0; i < populationSize; ++i)
  {
    p->addIndividual(&topology, &distribution);
  }
}
