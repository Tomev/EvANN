#include "normalizedSimpleScalingFunction.h"

/* Simple scaling function for minimalization problems proposed
 * by Engelbrecht in Computational Intelligence: An Introduction. */
double normalizedSimpleScalingFunction::scaleValue(double value)
{
  return maximalValue - value;
}
