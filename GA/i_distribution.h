#ifndef GENEVANN_DISTRIBUTION_H
#define GENEVANN_DISTRIBUTION_H


// Distributions interface.
class i_distribution {

public:
  virtual double getRandomNumberFromDistribution() = 0;

	// TODO: Add virtual destructor.
};


#endif //GENEVANN_DISTRIBUTION_H