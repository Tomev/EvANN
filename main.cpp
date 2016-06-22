#include <iostream>

#include "GA/individual.h"

using namespace std;

int main()
{
	// To pause console at some occasions.
	//string PAUSE;

	individual i;
	i.initialize(30);
	cout << i.toString() << endl;

	//cin >> PAUSE;
  return EXIT_SUCCESS;
}