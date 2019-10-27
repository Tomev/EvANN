//
// Created by Tomev on 27/10/2019.
//

#ifndef GENEVANN_LOGNORMALIZER_H
#define GENEVANN_LOGNORMALIZER_H

#include "i_normalizer.h"

class logNormalizer : public i_normalizer {
  public:
    double normalize(double const &value) override;
  private:
    double highestError = -1.0;
};


#endif //GENEVANN_LOGNORMALIZER_H
