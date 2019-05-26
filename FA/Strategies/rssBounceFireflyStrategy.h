#ifndef EVANN_RSSBOUNCEFIREFLYSTRATEGY_H
#define EVANN_RSSBOUNCEFIREFLYSTRATEGY_H

#include <vector>

using namespace std;

#include "neuralFireflyStrategy.h"

class RSSBounceFireflyStrategy : public neuralFireflyStrategy
{
  public:

    typedef double weight;
    typedef vector<weight> neuron; // Simplified
    typedef vector<neuron> layer;
    typedef vector<unsigned int> topology;

    RSSBounceFireflyStrategy(  double* stepSize, double* baseAttraction, double* absorption,
                            i_distribution* distribution, topology* top);

    void setSolution(void* newSolution) override;

    // ~neuralFireflyStrategy(); TODO
    // TODO: constant correctness

  protected:

    void generateRandomSolution(void *target, double stepSize = 1) override;
    void subtractThisSolutionFromGivenSolution(void* otherSolution, void* target) override;
    void addSolutionToThisSolution(void* otherSolution) override;
    void multiplySolution(void* target, double coefficient) override;
    double reduceToBounds(double val);

    double _lowerBound = -5;
    double _upperBound = 5;


};

#endif //EVANN_RSSBOUNCEFIREFLYSTRATEGY_H
