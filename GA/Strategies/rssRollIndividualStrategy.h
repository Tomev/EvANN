#ifndef EVANN_RSSROLLINDIVIDUALSTRATEGY_H
#define EVANN_RSSROLLINDIVIDUALSTRATEGY_H

#include "rssBounceIndividualStrategy.h"

class RSSRollIndividualStrategy : public RSSBounceIndividualStrategy{
  public:
    RSSRollIndividualStrategy(vector<unsigned int>* topology, i_distribution *distribution);
  protected:
    double reduceToBounds(double val) override;
};

#endif //EVANN_RSSROLLINDIVIDUALSTRATEGY_H
