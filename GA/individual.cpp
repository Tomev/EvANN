#include "individual.h"
#include <cstdlib>

void individual::mutate()
{

}

// Initializing solution vector with pseudo-random values.
void individual::initialize(int n)
{
  for(int i = 0; i < n; ++i) solution.push_back(getRandomDoubleWithinBounds());
}

individual individual::cross(const individual parent)
{
  individual child;
  int sec1, sec2;


  return child;
}

// Get random value within bounds defined in header.
double individual::getRandomDoubleWithinBounds()
{
  return (upperBound - lowerBound) * ( (double)rand() / (double)RAND_MAX ) + lowerBound;
}

string individual::toString()
{
	string result = "Solution: \n";

	for(int i = 0; i < solution.size(); ++i)
	{
		result +=  to_string(solution.at(i));
		result += ", ";

		// New line after 10 numbers.
		if(i % 10 == 9)
			result += "\n";
	}

	return result;
}

void individual::setEvaluationValue(double val)
{
	evaluationValue = val;
}