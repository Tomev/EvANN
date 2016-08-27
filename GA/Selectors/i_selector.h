#ifndef GENEVANN_I_SELECTOR_H
#define GENEVANN_I_SELECTOR_H

#include <vector>

#include "../individual.h"
#include "ScalingFunctions/i_scalingFunction.h"

class i_selector
{
public:
  virtual ~i_selector() = 0;

  virtual unsigned int selectIndividual() = 0;

  void setNewPopulation(std::vector<individual*>* population)
  {
    this->population = population;
  };

protected:
  std::vector<individual*>* population = 0;
  i_scalingFunction* scalingFunction;
};

#endif //GENEVANN_I_SELECTOR_H
