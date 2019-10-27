#ifndef GENEVANN_BOUNDEDNORMALIZER_H
#define GENEVANN_BOUNDEDNORMALIZER_H

#include "i_normalizer.h"

class boundedNormalizer : public i_normalizer {
  public:
    double normalize(double const &value) override;
  private:
    double limit = 10e5;
};


#endif //GENEVANN_BOUNDEDNORMALIZER_H
