#ifndef GENEVANN_EXPONENTIALDISTRIBUTION_H
#define GENEVANN_EXPONENTIALDISTRIBUTION_H

#include "i_distribution.h"

#include "cstdlib"
#include <random>

// Class for generating pseudo-random numbers according to exponential distribution.
class exponentialDistribution : public i_distribution{

public:
  exponentialDistribution();

  double getRandomNumberFromDistribution();

private:
  double lambda = 1;

  // Using exponential_distribution because distribution of weights in neural net is meant
  // to resemble one achieved by backpropagation (works by D. Montana).
  std::default_random_engine generator;
  std::exponential_distribution<double> distribution;
};


#endif //GENEVANN_EXPONENTIALDISTRIBUTION_H
