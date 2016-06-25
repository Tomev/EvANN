#include <iostream>

#include "GA/population.h"
#include "time.h"
#include "GA/exponentialDistribution.h"

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


  individual i1(&topology, &distribution);
  individual i2(&topology, &distribution);

  cout << "i1 " << i1.toString() << endl;
  cout << "i2 " << i2.toString() << endl;
  cout << "c " << i1.cross(&i2).toString() << endl;


	//cin >> PAUSE;
  return EXIT_SUCCESS;
}

void initializePopulation(population)
{

}