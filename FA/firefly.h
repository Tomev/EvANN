#ifndef GENEVANN_FIREFLY_H
#define GENEVANN_FIREFLY_H

#include <iostream>

#include "Strategies/i_fireflyStrategy.h"

// TODO: constant correctness

class firefly
{
public:

	firefly(i_fireflyStrategy* strategy);

	void initialize();
	void flyTowards(void* otherFireflyPosition);

	void setIllumination(double value);
	double getIllumination();
	void* getSolution();

	std::string toString();
	void print();

private:
	/* Usually higher the illumination, better the solution */
	double illumination;

	i_fireflyStrategy* strategy = NULL;

	bool hasStrategy();

};

#endif //GENEVANN_FIREFLY_H