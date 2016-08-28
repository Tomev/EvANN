#ifndef GENEVANN_ERRORBASEDPROGRESSINGSCALINGFUNCTION_H
#define GENEVANN_ERRORBASEDPROGRESSINGSCALINGFUNCTION_H

#include "i_scalingFunction.h"

class errorBasedProgressingScalingFunction : public i_scalingFunction
{
public:

  double scaleValue(double value);
  void setMaximalValue(double newValue);

protected:
  double maximalValue;
};

#endif //GENEVANN_ERRORBASEDPROGRESSINGSCALINGFUNCTION_H
