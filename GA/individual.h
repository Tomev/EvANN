#ifndef GENEVANN_I_INDIVIDUAL_H
#define GENEVANN_I_INDIVIDUAL_H

#include "Strategies/strategies.h"
#include "../Distributions/distributions.h"

class individual
{
public:

  individual(i_strategy* strategy);

  void mutate();
  void cross(void* solution, void* target);

  void setFitnessValue(double newValue);
  double getFitnessValue();

  void* getSolution();

  void print();

protected:
  double fitnessValue = 0.0;

  // TODO: Change to some kind of smart pointer.
  i_strategy* strategy;

};

#endif //GENEVANN_I_INDIVIDUAL_H
