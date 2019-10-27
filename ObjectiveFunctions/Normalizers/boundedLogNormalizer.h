//
// Created by Tomev on 27/10/2019.
//

#ifndef GENEVANN_BOUNDEDLOGNORMALIZER_H
#define GENEVANN_BOUNDEDLOGNORMALIZER_H

#include "i_normalizer.h"
#include <math.h>
#include <limits>

class boundedLogNormalizer : public i_normalizer {
  public:
    double normalize(double const &value) override;
  private:
    double limit = log10(std::numeric_limits<double>::max());
};


#endif //GENEVANN_BOUNDEDLOGNORMALIZER_H
