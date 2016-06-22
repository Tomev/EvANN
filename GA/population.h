#ifndef GENEVANN_POPULATION_H
#define GENEVANN_POPULATION_H

#include "individual.h"

class population {
public:
	void initialize(int individualSize);

	string toString();

protected:
	int populationSize = 50;
	vector<individual> individuals;


};

#endif //GENEVANN_POPULATION_H
