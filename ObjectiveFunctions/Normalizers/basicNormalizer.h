/*
 * Created by Tomev on 27/10/2019.
 *
 * This class is meant to normalize given values to set [0, 1], with respect to highest error that've been
 * encountered during normalization.
 *
 * It's worth noting, that due to dynamic nature of highest encountered error, this approach may not recognize which
 * of bad solutions is better than the other. Consider situation after initialization, when normalizator will get
 * two values -- 9 and 4958749057. Both these values will be in that case normalized to 1 -- which in the long run is
 * not desired. Note however, that this problem will only occur in initial stages of the normalizator usage and thus
 * has been considered acceptable.
 *
 * Another approach could be fixing error value to maximal possible value, however this'd be overkill considering, that
 * expected solutions are expected to be close to 0.
 *
 */


#ifndef GENEVANN_BASICNORMALIZER_H
#define GENEVANN_BASICNORMALIZER_H

#include "i_normalizer.h"

class basicNormalizer : public i_normalizer {
  public:
    double normalize(double const &value) override;
  private:
    double highestError = -1.0;

};


#endif //GENEVANN_BASICNORMALIZER_H
