#ifndef EVANN_RSSROLLFIREFLYSTRATEGY_H
#define EVANN_RSSROLLFIREFLYSTRATEGY_H

#include "rssBounceFireflyStrategy.h"

class RSSRollFireflyStrategy : public RSSBounceFireflyStrategy{
  public:

    RSSRollFireflyStrategy( double* stepSize, double* baseAttraction, double* absorption,
                            i_distribution* distribution, topology* top);

  protected:

    double reduceToBounds(double val) override;
};

#endif //EVANN_RSSROLLFIREFLYSTRATEGY_H
