#include <iostream>

#include "individual.h"

individual::individual(i_strategy* strategy) :
strategy(strategy)
{}

void individual::mutate()
{
  strategy->mutate();
}

void individual::setFitnessValue(double newValue)
{
  fitnessValue = newValue;
}

double individual::getFitnessValue()
{
  return fitnessValue;
}

void* individual::getSolution()
{
  strategy->getSolution();
}

void individual::print()
{
  cout << strategy->toString();
}

