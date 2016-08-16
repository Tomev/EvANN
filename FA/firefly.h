#ifndef GENEVANN_FIREFLY_H
#define GENEVANN_FIREFLY_H

#include <iostream>

#include "Strategies/i_fireflyStrategy.h"

// TODO: constant correctness

class firefly
{
public:

	firefly(i_fireflyStrategy* strategy)
	{
		this->strategy = strategy;
	}

	void initialize() { strategy->initialize();	}

	void flyTowards(void* otherFireflyPosition)
	{
		strategy->flyTowards(otherFireflyPosition);
	}

	void setIllumination(double value) {	illumination = value;	}
	double getIllumination() { return illumination;	}
	void* getSolution()	{	return strategy->getSolution(); }
	std::string toString() { return strategy->toString(); }
	void print(){ std::cout << this->toString() << std::endl; };

private:
	/* Usually higher the illumination, better the solution */
	double illumination;

	i_fireflyStrategy* strategy;

};

#endif //GENEVANN_FIREFLY_H