#include "errorBasedProgressingScalingFunction.h"

// Proposed by Engelbrecht for minimization problems.
double errorBasedProgressingScalingFunction::scaleValue(double value)
{
  return maximalValue - value;
}

void errorBasedProgressingScalingFunction::setMaximalValue(double newValue)
{
  maximalValue = newValue;
}