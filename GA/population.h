#ifndef GENEVANN_POPULATION_H
#define GENEVANN_POPULATION_H

#include "individual.h"

class population {
public:
	int mutationChancePercent = 5;
	int crossChancePercent = 5;

	vector<individual> individuals;

	void addIndividual(vector<int> *topology, i_distribution *distribution);
	void addIndividual(individual i);

	void normalizeFitnesses();

	string toString();
protected:


private:
	double findHighestFitnessValue();
};

#endif //GENEVANN_POPULATION_H
