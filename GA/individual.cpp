#include <iostream>

#include "individual.h"

individual::individual() {};

individual::individual(i_strategy* strategy) :
strategy(strategy)
{}

void individual::mutate()
{
  strategy->mutate();
}

void individual::cross(void *solution, individual* offspring)
{
  strategy->cross(solution, offspring->getSolution());
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

void individual::setSolution(void* newSolution)
{
  strategy->setSolution(newSolution);
}

void individual::print()
{
  cout << strategy->toString();
}

