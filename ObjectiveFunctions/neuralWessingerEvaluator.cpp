#include <iostream>
#include <cmath>

#include "neuralWessingerEvaluator.h"

neuralWessingerEvaluator::neuralWessingerEvaluator(neuralNet *nn)
	: nn(nn)
{}

// Count overall error of nn with weights given by solution
double neuralWessingerEvaluator::evaluate(void *solution)
{
	double error = 0.0;

	vector<neuralFireflyStrategy::layer>* target =
			static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

	// Set neural nets weights
	nn->setWeightsFromNeuronsStructure(target);

	vector<double> input;
	vector<double> output;
  double expectedVal, receivedVal, testCase;
	unsigned int denominator = 0;

  // For each test case (which are cases form 1.1 to 3.9)
  for(unsigned int t = 11; t < 40; ++t)
  {
    testCase = t;
    testCase /= 10;
    // Set nn input
    input.push_back(testCase);
    nn->setInputsValue(&input);
    // Feed forward
    nn->feedForward();
    // Get result
    nn->getResults(&output);
    // Add absolute difference between result and expected value
    expectedVal = sqrt(pow(testCase, 2) + 0.5);
    receivedVal = calculateOutputValue(testCase, output.at(0));

		error += pow(expectedVal - receivedVal, 2.0);

	  // Increase denominator for each test case
	  ++denominator;

		// Prepare vectors and nn for another iteration
		input.clear();
		output.clear();
    nn->resetNonInputLayerInputs();
	}

	return error / denominator;
}

// Evaluate and print error for each test case
void neuralWessingerEvaluator::printTestCases(void *solution)
{
  double overallError = 0.0;

  vector<neuralFireflyStrategy::layer>* target =
      static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

  // Set neural nets weights
  nn->setWeightsFromNeuronsStructure(target);

  vector<double> input;
  vector<double> output;
  double expectedVal, receivedVal, testCase;

  // For each test case (which are cases form 1.1 to 3.9)
  for(unsigned int t = 11; t < 40; ++t)
  {
    testCase = t;
    testCase /= 10;
    // Set nn input
    input.push_back(testCase);
    nn->setInputsValue(&input);
    // Feed forward
    nn->feedForward();
    // Get result
    nn->getResults(&output);
    // Add absolute difference between result and expected value
    expectedVal = sqrt(pow(testCase, 2) + 0.5);
    receivedVal = calculateOutputValue(testCase, output.at(0));

    cout << "t = " << testCase;
    cout << " expectedVal = " << expectedVal;
    cout << " receivedVal = " << receivedVal;
	  cout << " error = " << expectedVal - receivedVal << endl;

    overallError += pow((expectedVal-receivedVal), 2);


    // Prepare vectors and nn for another iteration
    input.clear();
    output.clear();
    nn->resetNonInputLayerInputs();
  }

  cout << "Total error: " << overallError << endl;
}

/* Calculates value of Wessinger equation for given input and
 * neural network output. The origin of "magic values" can be
 * found in work "Using Evolutionary Algorithms for solving a
 * differential Equation". */
double neuralWessingerEvaluator::calculateOutputValue(double input, double nnOutput)
{
	double result = sqrt(66) * (input-1) / 6;
	result -= sqrt(6) * (input - 4) / 6;
	result += (input -1) * (input - 4) * nnOutput;
	return result;
}