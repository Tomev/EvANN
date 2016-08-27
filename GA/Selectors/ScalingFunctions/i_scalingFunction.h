#ifndef GENEVANN_I_SCALINGFUNCTION_H
#define GENEVANN_I_SCALINGFUNCTION_H

class i_scalingFunction
{
public:
  //virtual ~i_scalingFunction() = 0;

  virtual double scaleValue(double value) = 0;
};

#endif //GENEVANN_I_SCALINGFUNCTION_H
