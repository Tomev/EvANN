#ifndef GENEVANN_I_NORMALIZER_H
#define GENEVANN_I_NORMALIZER_H

#include <memory>

class i_normalizer{
  public:
    virtual double normalize(double const &value) = 0;
};

typedef std::shared_ptr<i_normalizer> normalizerPtr;

#endif //GENEVANN_I_NORMALIZER_H
