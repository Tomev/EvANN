#include "neuralFireflyEvaluator.h"

neuralFireflyEvaluator::neuralFireflyEvaluator(neuralNet *nn)
	: nn(nn)
{}


// Count overall error of nn with weights given by solution
// TODO: FINISH THIS WHEN
double neuralFireflyEvaluator::evaluate(void *solution)
{
	double error = 0.0;

	vector<neuralFireflyStrategy::layer>* target = static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

	// Set neural nets weights
	nn->setWeightsFromNeuronsStructure(target);

	// For each test case
	for(unsigned int t = 0; t < 0 /* TODO */; ++t)
	{
		// Set nn inputs
		// Feed forward
		nn->feedForward();
		// Get results
		// Add absolute difference between result and expected value
	}

	return error;
}
