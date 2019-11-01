#include "basicNormalizer.h"

double basicNormalizer::normalize(double const &value) {
  if(value > highestError)
    highestError = value;
  return 1.0 - (value / highestError);
}
