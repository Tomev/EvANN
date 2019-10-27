#include <cstdlib>
#include <iostream>
#include "rouletteWheelSelector.h"

rouletteWheelSelector::rouletteWheelSelector(std::vector<individual> *population, int scalingFunctionId)
{
  // Set population on which selection will occur
  this->population = population;

  std::random_device rd;
  _gen = std::mt19937(rd());
  _uniformRealDistribution = std::uniform_real_distribution<>(0.0, 1.0);

  // Select scaling function basing on its ID
  switch(scalingFunctionId)
  {
    case normalizedSimpleScaling:
      scalingFunction = new normalizedSimpleScalingFunction();
      break;
    case errorBasedProgressing:
      scalingFunction = new errorBasedProgressingScalingFunction();
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

  // For each individual in population add its scaled fitness to sum
  for(auto individual : *population) sumOfScales += scalingFunction->scaleValue(individual.getFitnessValue());

  // Draw random threshold value form 0 to 1
  double threshold = _uniformRealDistribution(_gen);
  unsigned int i = 0;
  double sum = 0;

  // Continue searching until sum exceeds or equals threshold
  for(; i < population->size() - 1; ++i){
    if(threshold > sum) sum += scalingFunction->scaleValue(population->at(i).getFitnessValue()) / sumOfScales;
    else break;
  }

  return i;
}

void rouletteWheelSelector::setNewPopulation(std::vector<individual> *population)
{
  this->population = population;
};

void rouletteWheelSelector::setMaximalValue(double val)
{
  scalingFunction->setMaximalValue(val);
}

void rouletteWheelSelector::selectParents(unsigned int *p1, unsigned int *p2)
{
  // Initialize with 0
  *p1 = *p2 = 0;

  // Count sum of scales
  double sumOfScales = 0.0;

  // For each individual in population add its scaled fitness to sum
  for(auto individual : *population) sumOfScales += scalingFunction->scaleValue(individual.getFitnessValue());

  // Draw random threshold value form 0 to 1
  double threshold = _uniformRealDistribution(_gen);

  double sum = 0;

  // Continue searching until sum exceeds or equals threshold
  for(; *p1 < population->size() - 1; ++*p1)
  {
    if(threshold > sum) sum += scalingFunction->scaleValue(population->at(*p1).getFitnessValue())  / sumOfScales;
    else break;
  }

  do
  {
    *p2 = 0;

    threshold = _uniformRealDistribution(_gen);

    sum = 0;

    // Continue searching until sum exceeds or equals threshold
    for(; *p2 < population->size() - 1; ++*p2)
    {
      if(threshold > sum) sum += scalingFunction->scaleValue(population->at(*p2).getFitnessValue()) / sumOfScales;
      else break;
    }

  } while(*p1 == *p2);
}

rouletteWheelSelector::~rouletteWheelSelector() {
  delete scalingFunction;
}
