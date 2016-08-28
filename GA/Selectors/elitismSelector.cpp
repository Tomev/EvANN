#include <iostream>
#include "elitismSelector.h"

elitismSelector::elitismSelector(int type) : type(type)
{}

unsigned int elitismSelector::selectIndividual()
{
  switch(type)
  {
    case maximizing:
      return findHighestFitnessIndex();
    case minimizing:
      return findLowestFitnessIndex();
  }
}

void elitismSelector::setMaximalValue(double val)
{
}

void elitismSelector::setNewPopulation(std::vector<individual> *population)
{
  this->population = population;
}

unsigned int elitismSelector::findHighestFitnessIndex()
{
  // Initialize highest on 0
  unsigned int highestFitnessIndex = 0;

  // For each other individual in population
  for(unsigned int i = 1; i < population->size(); ++i)
  {
    if(population->at(highestFitnessIndex).getFitnessValue() > population->at(i).getFitnessValue())
      highestFitnessIndex = i;
  }

  return highestFitnessIndex;
}

unsigned int elitismSelector::findLowestFitnessIndex()
{
  // Initialize lowest on 0
  unsigned int lowestFitnessIndex = 0;

  // For each other individual in population
  for(unsigned int i = 1; i < population->size(); ++i)
  {
    if(population->at(lowestFitnessIndex).getFitnessValue() < population->at(i).getFitnessValue())
      lowestFitnessIndex = i;
  }

  return lowestFitnessIndex;
}

void elitismSelector::selectParents(unsigned int *p1, unsigned int *p2)
{
  switch(type)
  {
    case maximizing:
      findHighFitnessParents(p1, p2);
      break;
    case minimizing:
      findLowFitnessParents(p1, p2);
      break;
  }
}

void elitismSelector::findLowFitnessParents(unsigned int *p1, unsigned int *p2)
{
  // Initialize with 0
  *p1 = *p2 = 0;

  // Decide 2nd place
  if(population->at(1).getFitnessValue() > population->at(0).getFitnessValue()) *p1 = 1;
  else *p2 = 1;

  // For each other individual in population
  for(unsigned int i = 0; i < population->size(); ++i)
  {
    if(population->at(i).getFitnessValue() < population->at(*p1).getFitnessValue())
    {
      *p2 = *p1;
      *p1 = i;
    }
  }
}

void elitismSelector::findHighFitnessParents(unsigned int *p1, unsigned int *p2)
{
  // Initialize with 0
  *p1 = *p2 = 0;

  // Decide 2nd place
  if(population->at(1).getFitnessValue() > population->at(0).getFitnessValue()) *p1 = 1;
  else *p2 = 1;

  // For each other individual in population
  for(unsigned int i = 0; i < population->size(); ++i)
  {
    if(population->at(i).getFitnessValue() > population->at(*p1).getFitnessValue())
    {
      *p2 = *p1;
      *p1 = i;
    }
  }
}
