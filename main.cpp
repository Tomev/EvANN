#include <iostream>

#include "GA/population.h"
#include "time.h"

using namespace std;

int main()
{
	// To pause console at some occasions.
	//string PAUSE;

  // Set random seed for proper functioning of GA.
  srand(time(NULL));

  vector<int> topology = {3, 3, 2};
  int populationSize = 30;

  individual i(&topology);
  i.initialize();
  cout << i.toString();
  i.mutate();
  cout << i.toString();

	//population p;
  //p.initialize(populationSize, &topology);
	//cout << p.toString();


	//cin >> PAUSE;
  return EXIT_SUCCESS;
}