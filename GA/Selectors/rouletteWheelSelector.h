#ifndef GENEVANN_ROULETTEWHEELSELECTOR_H
#define GENEVANN_ROULETTEWHEELSELECTOR_H

#include "i_selector.h"
#include "ScalingFunctions/scalingFunctions.h"

class rouletteWheelSelector : public i_selector
{
public:

  rouletteWheelSelector(std::vector<individual>* population, int scalingFunctionId);

  unsigned int selectIndividual();

  void setNewPopulation(std::vector<individual>* population);
  void setMaximalValue(double val);
  void selectParents(unsigned int* p1, unsigned int* p2);

protected:
  std::vector<individual>* population = 0;
  i_scalingFunction* scalingFunction;
};


#endif //GENEVANN_ROULETTEWHEELSELECTOR_H
