#ifndef GENEVANN_ROULETTEWHEELSELECTOR_H
#define GENEVANN_ROULETTEWHEELSELECTOR_H

#include "i_selector.h"
#include "ScalingFunctions/scalingFunctions.h"

class rouletteWheelSelector : public i_selector
{
public:

  rouletteWheelSelector(std::vector<individual>* population, int scalingFunctionId);
  ~rouletteWheelSelector();

  unsigned int selectIndividual() override ;
  void setNewPopulation(std::vector<individual>* population) override ;
  void setMaximalValue(double val) override ;
  void selectParents(unsigned int* p1, unsigned int* p2) override ;

protected:
  std::vector<individual>* population = nullptr;
  i_scalingFunction* scalingFunction;

  std::uniform_real_distribution<> _uniformRealDistribution;
  std::mt19937 _gen;
};


#endif //GENEVANN_ROULETTEWHEELSELECTOR_H
