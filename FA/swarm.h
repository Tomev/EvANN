#ifndef GENEVANN_SWARM_H
#define GENEVANN_SWARM_H

#include <vector>
#include "firefly.h"

// TODO: constant corectness
// TODO: move declarations to other file

template <class soultionClass> class swarm
{
public:
	void initialize();

private:
	int size;
	std::vector<firefly<soultionClass>> population;

	/* Used to scale random movement */
	double stepSize = 0.1;
	i_fireflyStrategy* strategy;

};


#endif //GENEVANN_SWARM_H
