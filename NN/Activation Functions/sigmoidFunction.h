#ifndef GENEVANN_SIGMOIDFUNCTION_H
#define GENEVANN_SIGMOIDFUNCTION_H

#include <cassert>
#include "i_activationFunction.h"
#include "math.h"

class sigmoidFunction: public i_activationFunction {
public:
	double getOutput(double val)
	{
		return 1 / (1 + exp(-val));
	}
};

#endif //GENEVANN_SIGMOIDFUNCTION_H
