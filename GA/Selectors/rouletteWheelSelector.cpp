#include <cstdlib>
#include <iostream>
#include "rouletteWheelSelector.h"


rouletteWheelSelector::rouletteWheelSelector(std::vector<individual> *population, int scalingFunctionId)
{
  // Set population on which selection will occur
  this->population = population;

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

  // For each individual in population
  for(unsigned int i = 0; i < population->size(); ++i)
  {
    // Add its scaled fitness to sum
    sumOfScales += scalingFunction->scaleValue(population->at(i).getFitnessValue());
  }

  // Draw random threshold value form 0 to 1
  double threshold = ((double)rand() / (double)RAND_MAX);
  unsigned int i = 0;
  double sum = scalingFunction->scaleValue(population->at(i).getFitnessValue()) / sumOfScales;

  // Continue searching until sum exceeds or equals threshold
  while(threshold > sum)
  {
    // Check if another individual should be selected
    ++i;
    sum += scalingFunction->scaleValue(population->at(i).getFitnessValue());
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
  *p1 = *p2 = 0.0;

  // Count sum of scales
  double sumOfScales = 0.0;

  // For each individual in population
  for(unsigned int i = 0; i < population->size(); ++i)
  {
    // Add its scaled fitness to sum
    sumOfScales += scalingFunction->scaleValue(population->at(i).getFitnessValue());
  }

  // Draw random threshold value form 0 to 1
  double threshold = ((double)rand() / (double)RAND_MAX);

  double sum = scalingFunction->scaleValue(population->at(*p1).getFitnessValue()) / sumOfScales;

  // Continue searching until sum exceeds or equals threshold
  while(threshold > sum)
  {
    // Check if another individual should be selected
    ++*p1;
    sum += scalingFunction->scaleValue(population->at(*p1).getFitnessValue());
  }

  do
  {
    *p2 = 0;

    threshold = ((double)rand() / (double)RAND_MAX);

    sum = scalingFunction->scaleValue(population->at(*p2).getFitnessValue()) / sumOfScales;

    // Continue searching until sum exceeds or equals threshold
    while(threshold > sum)
    {
      // Check if another individual should be selected
      ++*p2;
      sum += scalingFunction->scaleValue(population->at(*p2).getFitnessValue());
    }

  } while(*p1 == *p2);
}