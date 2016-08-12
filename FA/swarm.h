#ifndef GENEVANN_SWARM_H
#define GENEVANN_SWARM_H

#include <vector>
#include "firefly.h"

// TODO: constant correctness
// TODO: move declarations to other file

template <typename soultionClass> class swarm
{

public:
	swarm(double* stepSize, double* baseAttraction, double* absorption,
				unsigned int size, i_distribution, void* specificArgs, ...)
	{

	}

	void initialize(unsigned int size)
	{
		// For each supposed firefly in swarm
		for(unsigned f = 0; f < size; ++f)
		{

		}
	};

private:

	std::vector<firefly<soultionClass>> population;
};


#endif //GENEVANN_SWARM_H
