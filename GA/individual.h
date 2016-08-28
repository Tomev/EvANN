#ifndef GENEVANN_I_INDIVIDUAL_H
#define GENEVANN_I_INDIVIDUAL_H

#include "Strategies/strategies.h"
#include "../Distributions/distributions.h"

class i_strategy;

class individual
{
public:

  individual();
  individual(i_strategy* strategy);

  void mutate();
  void cross(void* solution, individual* target);

  void setFitnessValue(double newValue);
  double getFitnessValue();

  void* getSolution();
  void setSolution(void* newSolution);

  void print();

protected:
  double fitnessValue = 0.0;

  //TR TODO: Change to some kind of smart pointer.
  i_strategy* strategy = NULL;
};

#endif //GENEVANN_I_INDIVIDUAL_H
