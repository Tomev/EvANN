#ifndef GENEVANN_POPULATION_H
#define GENEVANN_POPULATION_H

#include "individual.h"

class population {
public:
	void initialize(int populationSize, vector<int> *topology);

	string toString();

	int mutationChancePercent = 5;
protected:
	vector<individual> individuals;

};

#endif //GENEVANN_POPULATION_H
