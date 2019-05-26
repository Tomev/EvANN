#include "rssRollIndividualStrategy.h"

RSSRollIndividualStrategy::RSSRollIndividualStrategy(vector<unsigned int> *topology, i_distribution *distribution)
    : RSSBounceIndividualStrategy(topology, distribution)
{}

double RSSRollIndividualStrategy::reduceToBounds(double val) {
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


