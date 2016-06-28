#ifndef GENEVANN_POPULATION_H
#define GENEVANN_POPULATION_H

#include "individual.h"

class population {
public:

	void normalizeFitnesses();

	string toString();

	int mutationChancePercent = 5;
protected:


private:
	vector<individual> individuals;
	double findHighestFitnessValue();
	double normalizeValue(double target, double highestValue);

};

#endif //GENEVANN_POPULATION_H
