#ifndef GENEVANN_FIREFLY_H
#define GENEVANN_FIREFLY_H

#include <iostream>

#include "Strategies/i_fireflyStrategy.h"

// TODO: constant correctness

class firefly
{
public:

	firefly();
	firefly(i_fireflyStrategy* strategy);

	void initialize();
	void flyTowards(void* otherFireflyPosition);

	void setIllumination(double value);
	double getIllumination();
	void setEvaluationValue(double value);
	double getEvaluationValue();
	void* getSolution();
	void setSolution(void* newSolution);

	std::string toString();
	void print();

private:
	/* Usually higher the illumination, better the solution */
	double illumination;

	double evaluationValue = 0.0;

	i_fireflyStrategy* strategy = NULL;

	bool hasStrategy();

};

#endif //GENEVANN_FIREFLY_H