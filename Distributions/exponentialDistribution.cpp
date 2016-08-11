#include "exponentialDistribution.h"
#include "time.h"

static double randomlyTurnNegative(const double n);

exponentialDistribution::exponentialDistribution()
{
  distribution = std::exponential_distribution<double>(lambda);
  generator.seed(time(NULL));
}

double exponentialDistribution::getRandomNumberFromDistribution()
{
  return randomlyTurnNegative(distribution(generator));
};

double static randomlyTurnNegative(const double n)
{
  return (rand()%2 == 0) ? n : -n;
}