#ifndef GENEVANN_ELITISMSELECTOR_H
#define GENEVANN_ELITISMSELECTOR_H

#include "i_selector.h"

class elitismSelector : public i_selector
{
public:

  enum functionType
  {
    maximizing, minimizing
  };

  elitismSelector(int type);

  unsigned int selectIndividual();

  void setNewPopulation(std::vector<individual>* population);
  void setMaximalValue(double val);
  void selectParents(unsigned int* p1, unsigned int* p2);

protected:
  std::vector<individual>* population = 0;

private:
  int type;

  unsigned int findHighestFitnessIndex();
  unsigned int findLowestFitnessIndex();
  void findHighFitnessParents(unsigned int* p1, unsigned int* p2);
  void findLowFitnessParents(unsigned int* p1, unsigned int* p2);


};


#endif //GENEVANN_ELITISMSELECTOR_H
