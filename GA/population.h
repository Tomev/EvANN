#ifndef GENEVANN_POPULATION_H
#define GENEVANN_POPULATION_H

#include "individual.h"

class population {
public:
	int mutationChancePercent = 5;
	int crossChancePercent = 5;

	void addIndividual(vector<int> *topology, i_distribution *distribution);

	void normalizeFitnesses();

	string toString();
protected:


private:
	vector<individual> individuals;
	double findHighestFitnessValue();
};

#endif //GENEVANN_POPULATION_H
