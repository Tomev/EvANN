#ifndef GENEVANN_I_STRATEGY_H
#define GENEVANN_I_STRATEGY_H

#include <string>

class i_strategy
{
public:
  //virtual ~i_strategy() = 0;

  virtual void mutate() = 0;
  virtual void cross(void* solution, void* target) = 0;

  virtual void* getSolution() = 0;
  virtual void setSolution(void* newSolution) = 0;
  virtual std::string toString() = 0;
};


#endif //GENEVANN_I_STRATEGY
