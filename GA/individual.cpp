#include "individual.h"
#include "time.h"

#include <iostream>
#include <cstdlib>
#include <random>


void individual::mutate()
{

}

// Initializing solution vector with pseudo-random values with selected distribution.
void individual::initialize(int n)
{
  for(int i = 0; i < n; ++i)
	  solution.push_back(getRandomValueFromDoubleExponentialDistribution());
}

individual individual::cross(const individual parent)
{
  individual child;
  int sec1, sec2;


  return child;
}

// Returns e^(-|x|) for random x. This way distribution of weights in neural net
// is meant to resemble one achieved by backpropagation (works by D. Montana).
// Returns values from 0 to 1.
double individual::getRandomValueFromDoubleExponentialDistribution()
{
	std::default_random_engine generator;
	generator.seed(time(NULL));
	std::exponential_distribution<double> distribution(lambda);

	return distribution(generator);
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