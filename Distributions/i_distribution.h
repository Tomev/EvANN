#ifndef GENEVANN_DISTRIBUTION_H
#define GENEVANN_DISTRIBUTION_H


// Distributions interface.
class i_distribution {

public:

  virtual ~i_distribution() = 0;

  virtual double getRandomNumberFromDistribution() = 0;

};


#endif //GENEVANN_DISTRIBUTION_H
