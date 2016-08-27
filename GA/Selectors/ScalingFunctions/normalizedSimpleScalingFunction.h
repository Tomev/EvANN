#ifndef GENEVANN_NORMALIZEDSIMPLESCALINGFUNCTION_H
#define GENEVANN_NORMALIZEDSIMPLESCALINGFUNCTION_H

#include "i_scalingFunction.h"

/* This class is meant to scale normalized values and is used
 * in proportional selectors. */
class normalizedSimpleScalingFunction : public i_scalingFunction
{
public:

  double scaleValue(double value);

private:

  double maximalValue = 1.0;
};

#endif //GENEVANN_NORMALIZEDSIMPLESCALINGFUNCTION_H
