#include "logNormalizer.h"
#include <math.h>

double logNormalizer::normalize(double const &value) {
  double normalizedVal;
  if(value < 10) normalizedVal = value / 10.0; // Linear under 10
  else normalizedVal = log10(value);
  highestError = highestError > normalizedVal ? highestError : normalizedVal;
  return 1.0 - (normalizedVal / highestError);
}
