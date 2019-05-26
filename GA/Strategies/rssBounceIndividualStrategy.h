#ifndef EVANN_RSSBOUNCEINDIVIDUALSTRATEGY_H
#define EVANN_RSSBOUNCEINDIVIDUALSTRATEGY_H

#include "neuralIndividualStrategy.h"

class RSSBounceIndividualStrategy : public neuralIndividualStrategy{
  public:
    RSSBounceIndividualStrategy(vector<unsigned int>* topology, i_distribution *distribution);
    void setSolution(void *newSolution) override;

  protected:

    double _upperBound = 5;
    double _lowerBound = -5;

    void nodeMutation() override;
    void initializeSolution() override;

    double reduceToBounds(double val);


};

#endif //EVANN_RSSBOUNCEINDIVIDUALSTRATEGY_H
