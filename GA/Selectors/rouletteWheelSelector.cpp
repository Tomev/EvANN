#include <cstdlib>
#include "rouletteWheelSelector.h"
#include "ScalingFunctions/scalingFunctions.h"

rouletteWheelSelector::rouletteWheelSelector(std::vector<individual *> *population, int scalingFunctionId)
{
  // Set population on which selection will occur
  this->population = population;

  // Select scaling function basing on its ID
  switch(scalingFunctionId)
  {
    case normalizedSimpleScalingFunction:
      scalingFunction = new normalizedSimpleScalingFunction();
      break;
    default:
      break;
  }
}

// Selects individual and returns its position
unsigned int rouletteWheelSelector::selectIndividual()
{
  // Count sum of scales
  double sumOfScales = 0.0;

  // For each individual in population
  for(unsigned int i = 0; i < population->size(); ++i)
  {
    // Add its scaled fitness to sum
    sumOfScales += scalingFunction->scaleValue(population->at(i)->getFitnessValue());
  }

  // Draw random threshold value form 0 to 1
  double threshold = ((double)rand() / (double)RAND_MAX);

  unsigned int i = 0;
  double sum = scalingFunction->scaleValue(population->at(i)->getFitnessValue());

  // Continue searching until sum exceeds or equals threshold
  while(threshold < sum)
  {
    // Check if another individual should be selected
    ++i;
    threshold += scalingFunction->scaleValue(population->at(i)->getFitnessValue());
  }

  return i;
}