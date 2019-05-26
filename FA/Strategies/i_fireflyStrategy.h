#ifndef GENEVANN_I_FIREFLYSTRATEGY_H
#define GENEVANN_I_FIREFLYSTRATEGY_H

#include <string>

#include "../../Distributions/i_distribution.h"

class i_fireflyStrategy
{
public:

	virtual void* getSolution() = 0;
	virtual void setSolution(void* newSolution) = 0;
	virtual void initialize() = 0;
	virtual void flyTowards(void* otherFireflyPosition) = 0;
	virtual std::string toString() = 0;
	~i_fireflyStrategy() {};

	// TODO: constant correctness

protected:

	virtual double countSquareDistance(void* otherFireflyPosition) = 0;
	virtual double countAttraction(double squareDistance) = 0;
	virtual void generateRandomSolution(void* target, double stepSize = 1) = 0;
	virtual void subtractThisSolutionFromGivenSolution(void* otherSolution, void* target) = 0;
	virtual void addSolutionToThisSolution(void* otherSolution) = 0;
	virtual void multiplySolution(void* target, double coefficient) = 0;
	virtual bool hasProperType(void* target) = 0;



	i_distribution* distribution = 0;
	double* baseAttraction = 0;
	double* stepSize = 0;
	double* absorption = 0;
};

#endif //GENEVANN_I_FIREFLYSTRATEGY_H
