#ifndef GENEVANN_INDIVIDUAL_H
#define GENEVANN_INDIVIDUAL_H

#include <vector>
#include <string>
#include <math.h>

using namespace std;

class individual {

public:
	void mutate();
  void initialize(int n);
  individual cross(const individual parent);
	string toString();

	void setEvaluationValue(double val);
	double getEvaluationValue();

protected:
  vector<double> solution;

	double evaluationValue;

	// Used as argument in random number generation in exponential distribution.
	double lambda = 3.5;

	double getRandomValueFromDoubleExponentialDistribution();

};

#endif //GENEVANN_INDIVIDUAL_H