#ifndef GENEVANN_NEURALFIREFLYSTRATEGY_H
#define GENEVANN_NEURALFIREFLYSTRATEGY_H

#include <vector>

using namespace std;

#include "i_fireflyStrategy.h"

class neuralFireflyStrategy : public i_fireflyStrategy
{
public:

	typedef double weight;
	typedef vector<weight> neuron; // Simplified
	typedef vector<neuron> layer;
	typedef vector<unsigned int> topology;

	neuralFireflyStrategy(  double* stepSize, double* baseAttraction, double* absorption,
													i_distribution* distribution, topology* top);
	void setSolution(void* solution);
	void initialize();
	void flyTowards(void* otherFireflyPosition);
	string toString();

	// ~neuralFireflyStrategy(); TODO
	// TODO: constant corectness

protected:

	void generateRandomSolution(void *target, double stepSize = 1);
	double countSquareDistance(void* otherFireflyPosition);
	double countAttraction(double squareDistance);
	void subtractThisSolutionFromGivenSolution(void* otherSolution, void* target);
	void addSolutionToThisSolution(void* otherSolution);
	void multiplySolution(void* target, double coefficient);
	bool hasProperType(void* target);

private:

	vector<layer>* solution;
	topology* structure;

};


#endif //GENEVANN_NEURALFIREFLYSTRATEGY_H
