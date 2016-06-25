#include "exponentialDistribution.h"
#include "time.h"

exponentialDistribution::exponentialDistribution()
{
  distribution = std::exponential_distribution<double>(lambda);
  generator.seed(time(NULL));
}

double exponentialDistribution::getRandomNumberFromDistribution()
{
  return randomlyTurnNegative(distribution(generator));
};

// 50% chance to negate passed number.
double exponentialDistribution::randomlyTurnNegative(const double n)
{
  return n; //(rand()%2 == 0) ? n : -n;
}