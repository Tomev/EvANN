#include <typeinfo>
#include <iostream>
#include <math.h>
#include <cassert>

#include "rssBounceFireflyStrategy.h"

RSSBounceFireflyStrategy::RSSBounceFireflyStrategy
  ( double *stepSize,
    double *baseAttraction,
    double *absorption,
    i_distribution *distribution,
    vector<unsigned int>* top  )
    : neuralFireflyStrategy(stepSize, baseAttraction, absorption, distribution, top)
{}

void RSSBounceFireflyStrategy::setSolution(void *newSolution)
{
  /* As copying pointer won't do the trick each value in current
 * individuals solution vector is replaced by adequate value from
 * new solution. Note that size of new solution and current solution
 * are meant to be same. */

  vector<layer>* parent = (vector<layer>*) newSolution;

  assert(parent->size() == solution->size());

  // For each layer
  for(unsigned int l = 0; l < solution->size(); ++l)
  {
    assert(parent->at(l).size() == solution->at(l).size());

    // For each neuron on that layer
    for(unsigned int n = 0; n < solution->at(l).size(); ++n)
    {
      assert(parent->at(l).at(n).size() == solution->at(l).at(n).size());

      // For each weight of that neuron
      for(unsigned int w = 0; w < solution->at(l).at(n).size(); ++w)
      {
        // Replace solutions value at current weight
        solution->at(l).at(n).at(w) = reduceToBounds(parent->at(l).at(n).at(w));
      }
    }
  }
}

/* Initialize target solution with 3D vector */
void RSSBounceFireflyStrategy::generateRandomSolution(void *target, double stepSize)
{
  vector<layer>* t;

  if(hasProperType(target)) t = static_cast<vector<layer>*>(target);
  else return;

  /* For each non-output layer (all topology positions excluding last), because output
   * neurons doesn't have any outgoing connections and thus any weights */
  unsigned int nonOutputLayersNumber = structure->size()-1;

  for(unsigned int i = 0; i < nonOutputLayersNumber; ++i)
  {
    // Add layer to the solution
    t->push_back(layer());

    // For each neuron destined to be in this layer
    unsigned int currentLayerNeuronNumber = structure->at(i);

    for(unsigned int j = 0; j < currentLayerNeuronNumber; ++j)
    {
      // Add neuron to the solution
      t->at(i).push_back(neuron());

      // For each neuron in next layer + bias
      unsigned int nextLayerNo = i+1;
      for(int k = 0; k < structure->at(nextLayerNo) + 1; ++k)
      {
        // Add random weight from selected distribution to current neuron
        double weight = distribution->getRandomNumberFromDistribution() * stepSize;

        t->at(i).at(j).push_back(reduceToBounds(weight));
      }
    }
  }
}

void RSSBounceFireflyStrategy::multiplySolution(void *target, double coefficient)
{
  vector<layer>* modified;

  if(hasProperType(target)) modified = static_cast<vector<layer>*>(target);
  else return;

  // For each layer of solution (position could be used instead of solution)
  for(unsigned int i = 0; i < modified->size(); ++i)
  {
    // For each neuron in that layer
    for(unsigned int j = 0; j < modified->at(i).size(); ++j)
    {
      // For each weight of that neuron
      for(unsigned int k = 0; k < modified->at(i).at(j).size(); ++k)
      {
        // Multiply solutions k-th element accordingly to coefficient
        double newWeight = reduceToBounds((*modified)[i][j][k] * coefficient);
        modified->at(i).at(j).at(k) = newWeight;

        // TODO TR: Add bounds to weights
      }
    }
  }
}

void RSSBounceFireflyStrategy::subtractThisSolutionFromGivenSolution(void *otherSolution, void *target)
{
  vector<layer>* difference;
  vector<layer>* minuend;

  if(hasProperType(otherSolution))  minuend = static_cast<vector<layer>*>(otherSolution);
  else return;

  if(hasProperType(target)) difference = static_cast<vector<layer>*>(target);
  else return;

  // For each layer of solution (minuend could be used instead of solution)
  for(unsigned int i = 0; i < solution->size(); ++i)
  {
    // Push layer to difference
    difference->push_back(layer());

    // For each neuron in that layer
    for(unsigned int j = 0; j < solution->at(i).size(); ++j)
    {
      // Push neuron to that layer in difference
      difference->at(i).push_back(neuron());

      // For each weight of that neuron
      for(unsigned int k = 0; k < solution->at(i).at(j).size(); ++k)
      {
        // Subtract that weight from the same weight in minuend
        double dif = minuend->at(i).at(j).at(k) - solution->at(i).at(j).at(k);

        // Push result to differences current neuron
        difference->at(i).at(j).push_back(reduceToBounds(dif));
      }
    }
  }
}

void RSSBounceFireflyStrategy::addSolutionToThisSolution(void *otherSolution)
{
  vector<layer>* addend;

  if(hasProperType(otherSolution)) addend = static_cast<vector<layer>*>(otherSolution);
  else return;

  // For each layer of solution (addend could be used instead of solution)
  for(unsigned int i = 0; i < solution->size(); ++i)
  {
    // For each neuron in that layer
    for(unsigned int j = 0; j < solution->at(i).size(); ++j)
    {
      // For each weight of that neuron
      for(unsigned int k = 0; k < solution->at(i).at(j).size(); ++k)
      {
        // Add addend corresponding element to solution

        double newSolutionValue = reduceToBounds((*solution)[i][j][k] + (*addend)[i][j][k]);
        solution->at(i).at(j).at(k) = newSolutionValue;
      }
    }
  }
}

// In strategies with RSS this should be called before assigning weight
double RSSBounceFireflyStrategy::reduceToBounds(double val)
{
  double reducedValue = val;

  while(reducedValue > _upperBound || reducedValue < _lowerBound){
    if (val < _lowerBound){
      reducedValue = _lowerBound - (reducedValue - _lowerBound);
    }
    else if (reducedValue > _upperBound){
      reducedValue = _upperBound - (reducedValue - _upperBound);
    }
  }

  //cout << "Reduced val: " << reducedValue << endl;

  return reducedValue;
}