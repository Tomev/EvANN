#include <iostream>

#include "alternativeNeuralWessingerEvaluator.h"

alternativeNeuralWessingersEvaluator::alternativeNeuralWessingersEvaluator(neuralNet *nn)
	: nn(nn)
{}

// Count overall error of nn with weights given by solution
double alternativeNeuralWessingersEvaluator::evaluate(void *solution)
{
	double error = 0.0;

	vector<neuralFireflyStrategy::layer>* target =
		static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

	// Set neural nets weights
	nn->setWeightsFromNeuronsStructure(target);

	vector<double> input;
	vector<double> output;
	double testCase;
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
		error += pow(calculateOutputValue(testCase, output.at(0)), 2);

		// Increase denominator for each test case
		++denominator;

		// Prepare vectors and nn for another iteration
		input.clear();
		output.clear();
		nn->resetNonInputLayerInputs();
	}

	return error;// / denominator;
}

// Evaluate and print error for each test case
void alternativeNeuralWessingersEvaluator::printTestCases(void *solution)
{
	double overallError = 0.0;

	vector<neuralFireflyStrategy::layer>* target =
		static_cast<vector<neuralFireflyStrategy::layer>*>(solution);

	// Set neural nets weights
	nn->setWeightsFromNeuronsStructure(target);

	vector<double> input;
	vector<double> output;
	double receivedVal, testCase;

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
		receivedVal = calculateOutputValue(testCase, output.at(0));

		cout << "t = " << testCase;
		cout << " receivedVal = " << receivedVal << endl;

		overallError += pow((receivedVal), 2);

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
double alternativeNeuralWessingersEvaluator::calculateOutputValue(double input, double nnOutput)
{
	double t = input;

	double result = t * pow(trialFunctionValue(t, nnOutput), 2) * pow(trialFunctionDerivativeValue(t, nnOutput), 2);
	result -= pow(trialFunctionValue(t,nnOutput), 3) * pow(trialFunctionDerivativeValue(t, nnOutput), 2);
	result += t * (pow(t, 2) + 1) * trialFunctionDerivativeValue(t, nnOutput);
	result -= t * t * trialFunctionValue(t, nnOutput);

	return result;
}

double alternativeNeuralWessingersEvaluator::trialFunctionValue(double t, double nnOutput)
{
	double result = 1/6 * (t-1) * sqrt(66);
	result -= 1/6 * (t-4) *sqrt(6);
	result += (t-1) * (t-4) * nnOutput;

	return result;
}

double alternativeNeuralWessingersEvaluator::trialFunctionDerivativeValue(double t, double nnOutput)
{
	double result = sqrt(66) / 6;
	result -= sqrt(6) / 6;
	result += 4 * trialFunctionNNPartDerivativeValue(t);
	result += t * t * nnOutput * nnOutput;
	result += 2 * t * nnOutput;
	result -= 5 * nnOutput;
	result -= 5 * t * trialFunctionNNPartDerivativeValue(t);

	return result;
}

// Note that it's counted for ANN with a single layer
double alternativeNeuralWessingersEvaluator::trialFunctionNNPartDerivativeValue(double t)
{
	double result = 0.0;
	double component;

	for(unsigned int i = 0; i < nn->getTopology()->at(1); ++i)
	{
		component = - pow((1 / (1 + exp(-( nn->getNeuronsIthOutputWeight(1, i, 0)) * t + nn->getNeuronsBias(1, i) ))), 2);

		component += (1 / (1 + exp(-( nn->getNeuronsIthOutputWeight(1, i, 0) * t + nn->getNeuronsBias(1, i)))));

		component *= nn->getNeuronsIthOutputWeight(1, i, 0) * nn->getNeuronsIthOutputWeight(0, 0, i);

		result += component;
	}

	//cout << result << endl;

	return result;
}