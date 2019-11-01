//
// Created by Tomev on 27/10/2019.
//

#include "boundedNormalizer.h"

double boundedNormalizer::normalize(double const &value) {
  if(value > limit) return 0;
  return 1.0 - (value / limit);
}
