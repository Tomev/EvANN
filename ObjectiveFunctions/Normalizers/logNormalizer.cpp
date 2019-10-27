#include "logNormalizer.h"
#include <math.h>

double logNormalizer::normalize(double const &value) {
  double normalizedVal = log10(value);
  highestError = highestError > normalizedVal ? highestError : normalizedVal;
  return 1.0 - (normalizedVal / highestError);
}
