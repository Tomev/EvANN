#ifndef GENEVANN_LINEARFUNCTION_H
#define GENEVANN_LINEARFUNCTION_H

#include "i_activationFunction.h"

class linearFunction : public i_activationFunction
{
public:
	double getOutput(double val)
	{
		return slope * val + yIntercept;
	}
private:
	double slope = 1.0; // a coefficient
	double yIntercept = 0.0; // b coefficient
};

#endif //GENEVANN_LINEARFUNCTION_H
