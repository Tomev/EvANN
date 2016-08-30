#ifndef GENEVANN_I_ACTIVATIONFUNCTION_H
#define GENEVANN_I_ACTIVATIONFUNCTION_H

#include <vector>

class i_activationFunction {
public:
	virtual double getOutput(double val) = 0;

	// TODO: Add virtual destructor.
};

#endif //GENEVANN_I_ACTIVATIONFUNCTION_H
