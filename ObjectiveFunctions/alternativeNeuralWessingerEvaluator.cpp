#include <iostream>

#include "alternativeNeuralWessingerEvaluator.h"
#include "Normalizers/normalizers.h"

alternativeNeuralWessingersEvaluator::alternativeNeuralWessingersEvaluator(neuralNet *nn)
	: nn(nn), _normalizer(make_shared<logNormalizer>())
{}

// Count overall error of nn with weights given by solution
double alternativeNeuralWessingersEvaluator::evaluate(void *solution)
{
	double error = 0.0;

	auto target = static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

	// Set neural nets weights
	nn->setWeightsFromNeuronsStructure(target);

	vector<double> input;
	vector<double> output;
	double testCase;
	unsigned int denominator = 0;

	// For each test case (which are cases form 1 to 4)
	for(unsigned int t = 10; t <= 40; ++t)
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
		error += pow(calculateOutputValue(testCase, output.at(0)), 2);

		// Increase denominator for each test case
		++denominator;

		// Prepare vectors and nn for another iteration
		input.clear();
		output.clear();
		nn->resetNonInputLayerInputs();
	}

	return _normalizer->normalize(error);
}

// Evaluate and print error for each test case
void alternativeNeuralWessingersEvaluator::printTestCases(void *solution)
{
	double overallError = 0.0;

	auto target = static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

	// Set neural nets weights
	nn->setWeightsFromNeuronsStructure(target);

	vector<double> input;
	vector<double> output;
	double receivedVal, testCase;

	// For each test case (which are cases form 1 to 4)
	for(unsigned int t = 10; t <= 40; ++t)
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
		receivedVal = calculateOutputValue(testCase, output.at(0));

		/*
		cout << "t = " << testCase;
		cout << " receivedVal = " << receivedVal << endl;

		cout << "Expected trial = " << sqrt(testCase * testCase + 0.5);
		cout << " Actual Trial = " << trialFunctionValue(testCase, output.at(0)) << endl;
		*/

		overallError += pow((receivedVal), 2);

		// Prepare vectors and nn for another iteration
		input.clear();
		output.clear();
		nn->resetNonInputLayerInputs();
	}

	//cout << "Total error: " << overallError << endl;
  cout << overallError << endl;
}

/* Calculates value of Wessinger equation for given input and
 * neural network output. The origin of "magic values" can be
 * found in work "Using Evolutionary Algorithms for solving a
 * differential Equation". */
double alternativeNeuralWessingersEvaluator::calculateOutputValue(double input, double nnOutput)
{
	double t = input;

	double result = (t - trialFunctionValue(t, nnOutput));
  result *= pow(trialFunctionValue(t, nnOutput)* trialFunctionDerivativeValue(t, nnOutput),2);
	result += t * (t * t + 1.f) * trialFunctionDerivativeValue(t, nnOutput);
	result -= t * t * trialFunctionValue(t, nnOutput);

	return result;
}

double alternativeNeuralWessingersEvaluator::trialFunctionValue(double t, double nnOutput)
{
	double result = (sqrt(66.f) / 6.f) * (t - 1.f);
	result -= (sqrt(6.f) / 6.f) * (t-4.f);
	result += (t - 1.f) * (t - 4.f) * nnOutput;

	return result;
}

double alternativeNeuralWessingersEvaluator::trialFunctionDerivativeValue(double t, double nnOutput)
{
	double result = (sqrt(66.f) - sqrt(6.f)) / 6.f;

	result += (t * t - 5.f * t + 4.f) * trialFunctionNNPartDerivativeValue(t);

	result += (2.f * t - 5.f) * nnOutput;

	return result;
}

// Note that it's counted for ANN with a single layer
double alternativeNeuralWessingersEvaluator::trialFunctionNNPartDerivativeValue(double t)
{
	double result = 0.0;
	double component, element, powerElement;

	for(unsigned int i = 0; i < nn->getTopology()->at(1); ++i)
	{
		powerElement = -((nn->getNeuronsIthOutputWeight(0, 0, i)) * t  + nn->getNeuronsBias(1, i));
		element = 1.f / (1.f + exp (powerElement));

		component = - pow(element, 2);

		component += element;

		component *= nn->getNeuronsIthOutputWeight(1, i, 0) * nn->getNeuronsIthOutputWeight(0, 0, i);

		result += component;
	}

	return result;
}