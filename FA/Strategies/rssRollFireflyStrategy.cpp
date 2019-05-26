#include "rssRollFireflyStrategy.h"

RSSRollFireflyStrategy::RSSRollFireflyStrategy
    ( double *stepSize,
      double *baseAttraction,
      double *absorption,
      i_distribution *distribution,
      vector<unsigned int>* top  )
    : RSSBounceFireflyStrategy(stepSize, baseAttraction, absorption, distribution, top)
{}

double RSSRollFireflyStrategy::reduceToBounds(double val) {
  double reducedValue = val;

  while(reducedValue > _upperBound || reducedValue < _lowerBound){
    if(reducedValue > _upperBound){
      reducedValue = _lowerBound + (reducedValue - _upperBound);
    }
    else if(reducedValue < _lowerBound){
      reducedValue = _upperBound - (_lowerBound - reducedValue);
    }
  }

  return reducedValue;
}
