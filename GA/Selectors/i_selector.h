#ifndef GENEVANN_I_SELECTOR_H
#define GENEVANN_I_SELECTOR_H

#include <vector>

#include "../individual.h"
#include "ScalingFunctions/i_scalingFunction.h"

class i_selector
{
public:
  //virtual ~i_selector() = 0;

  virtual unsigned int selectIndividual() = 0;

  virtual void selectParents(unsigned int* p1, unsigned int* p2) = 0;
  virtual void setNewPopulation(std::vector<individual>* population) = 0;
  virtual void setMaximalValue(double val) = 0;

protected:
  std::vector<individual>* population = 0;
  i_scalingFunction* scalingFunction;
};

#endif //GENEVANN_I_SELECTOR_H
