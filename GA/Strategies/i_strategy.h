#ifndef GENEVANN_STRATEGY_H
#define GENEVANN_STRATEGY_H

#include <string>

class i_strategy
{
public:
  virtual ~i_strategy() = 0;

  void mutate();

  void* getSolution();
  void setSolution(void* newSolution);
  virtual std::string toString() = 0;
};


#endif //GENEVANN_STRATEGY
