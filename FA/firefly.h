#ifndef GENEVANN_FIREFLY_H
#define GENEVANN_FIREFLY_H

#include <iostream>

#include "Strategies/i_fireflyStrategy.h"

// TODO: constant correctness
// TODO: move declarations to other file

template <typename solutionClass> class firefly
{
public:

	firefly(i_fireflyStrategy* strategy)
	{
		solution = new solutionClass();
		this->strategy = strategy;
		this->strategy->setSolution(solution);
	}

	void initialize() { strategy->initialize();	}

	void flyTowards(solutionClass* otherFireflyPosition)
	{
		strategy->flyTowards(otherFireflyPosition);
	}

	void setIllumination(double value) {	illumination = value;	}
	double getIllumination() { return illumination;	}
	solutionClass* getSolution()	{	return solution; }
	std::string toString() { return strategy->toString(); }
	void print(){ std::cout << this->toString() << std::endl; };

private:
	/* Usually higher the illumination, better the solution */
	double illumination;

	solutionClass* solution;
	i_fireflyStrategy* strategy;

};

#endif //GENEVANN_FIREFLY_H