//
// Created by Tomev on 27/10/2019.
//

#include "boundedLogNormalizer.h"

double boundedLogNormalizer::normalize(double const &value) {
  double normalizedVal = log10(value);
  return 1.0 - (normalizedVal / limit);
}
