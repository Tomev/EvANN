#ifndef GENEVANN_ROULETTEWHEELSELECTOR_H
#define GENEVANN_ROULETTEWHEELSELECTOR_H

#include "i_selector.h"
#include "ScalingFunctions/scalingFunctions.h"

class rouletteWheelSelector : public i_selector
{
public:

  rouletteWheelSelector(std::vector<individual>* population, int scalingFunctionId);

  unsigned int selectIndividual();

protected:
  std::vector<individual>* population = 0;
  i_scalingFunction* scalingFunction;
};


#endif //GENEVANN_ROULETTEWHEELSELECTOR_H
