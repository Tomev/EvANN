#ifndef GENEVANN_INDIVIDUAL_H
#define GENEVANN_INDIVIDUAL_H

#include <vector>;
#include <string>

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

	double  lowerBound = -1.0,
					upperBound = 1.0,
					evaluationValue;

	double getRandomDoubleWithinBounds();

};

#endif //GENEVANN_INDIVIDUAL_H