#include "normalizedSimpleMaximizationScalingFunction.h"

/* Simple scaling function for maximalization problems proposed
 * by Engelbrecht in Computational Intelligence: An Introduction. */
double normalizedSimpleScalingFunction::scaleValue(double value)
{
  return 1 / (1 + maximalValue - value);
}
// This value shouldn't be changed.
void normalizedSimpleScalingFunction::setMaximalValue(double newValue) {}