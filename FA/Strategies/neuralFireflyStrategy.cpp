#include <typeinfo>
#include <iostream>
#include <math.h>

#include "neuralFireflyStrategy.h"

neuralFireflyStrategy::neuralFireflyStrategy
	( double *stepSize,
		double *baseAttraction,
		double *absorption,
		i_distribution *distribution,
		vector<unsigned int>* top  )
{
	this->stepSize = stepSize;
	this->baseAttraction = baseAttraction;
	this->absorption = absorption;
	this->distribution = distribution;
	this->structure = top;

	this->solution = new vector<layer>();
}

/* TODO: Find out the problem
neuralFireflyStrategy::~neuralFireflyStrategy()
{
	delete solution;
	delete structure;
	delete distribution;
	delete baseAttraction;
	delete stepSize;
	delete absorption;
}
*/

void* neuralFireflyStrategy::getSolution()
{
	return solution;
}

/* Initialize solution with random values from given distribution and structure. */
void neuralFireflyStrategy::initialize()
{
	neuralFireflyStrategy::generateRandomSolution(solution);
}

/* Initialize target solution with 3D vector */
void neuralFireflyStrategy::generateRandomSolution(void *target, double stepSize)
{
	vector<layer>* t;

	if(hasProperType(target)) t = static_cast<vector<layer>*>(target);
	else return;

	/* For each non-output layer (all topology positions excluding last), because output
	 * neurons doesn't have any outgoing connections and thus any weights */
	unsigned int nonOutputLayersNumber = structure->size()-1;

	for(unsigned int i = 0; i < nonOutputLayersNumber; ++i)
	{
		// Add layer to the solution
		t->push_back(layer());

		// For each neuron destined to be in this layer
		unsigned int currentLayerNeuronNumber = structure->at(i);

		for(unsigned int j = 0; j < currentLayerNeuronNumber; ++j)
		{
			// Add neuron to the solution
			t->at(i).push_back(neuron());

			// For each neuron in next layer
			unsigned int nextLayerNo = i+1;
			for(int k = 0; k < structure->at(nextLayerNo); ++k)
			{
				// Add random weight from selected distribution to current neuron
				double weight = distribution->getRandomNumberFromDistribution() * stepSize;

				t->at(i).at(j).push_back(weight);
			}
		}
	}
}

/* Modifying solution according to basic formula (eg. wikipedia) */
void neuralFireflyStrategy::flyTowards(void* otherFireflyPosition)
{
	// Generate sum element corresponding to random direction.
	vector<layer> randomDirection;
	generateRandomSolution(&randomDirection, *stepSize);

	addSolutionToThisSolution(&randomDirection);

	// If there is no other firefly position specified, firefly should fly in random direction only.
	if(otherFireflyPosition == NULL) return;

	// Else also fly towards other firefly
	double squareDistance = countSquareDistance(otherFireflyPosition);

	// Abort operations if squared distance is lower than 0
	if(squareDistance < 0.0)
	{
		return;
	}

	double attraction = countAttraction(squareDistance);

	// Count sum element corresponding to other firefly direction.
	vector<layer> othersDirection;
	subtractThisSolutionFromGivenSolution(otherFireflyPosition, &othersDirection);
	multiplySolution(&othersDirection, attraction);

	// Add both elements to solution
	addSolutionToThisSolution(&othersDirection);

}

double neuralFireflyStrategy::countSquareDistance(void *otherFireflyPosition)
{
	vector<layer>* position;

	if(hasProperType(otherFireflyPosition)) position = static_cast<vector<layer>*>(otherFireflyPosition);
	else return -1.0;

	double distance = 0.0;

	// For each layer of solution (solution could be used instead of position.
	for(unsigned int i = 0; i < position->size(); ++i)
	{
		// For each neuron in that layer
		for(unsigned int j = 0; j < position->at(i).size(); ++j)
		{
			// For each weight of that neuron
			for(unsigned int k = 0; k < position->at(i).at(j).size(); ++k)
			{
				// Increase square distance accordingly to k-th elements
				distance +=	pow(position->at(i).at(j).at(k),2) + pow(solution->at(i).at(j).at(k), 2);
			}
		}
	}

	return distance;
}

double neuralFireflyStrategy::countAttraction(double squareDistance)
{
	return *baseAttraction * exp(-squareDistance * *absorption);
}

void neuralFireflyStrategy::multiplySolution(void *target, double coefficient)
{
	vector<layer>* modified;

	if(hasProperType(target)) modified = static_cast<vector<layer>*>(target);
	else return;

	// For each layer of solution (position could be used instead of solution)
	for(unsigned int i = 0; i < modified->size(); ++i)
	{
		// For each neuron in that layer
		for(unsigned int j = 0; j < modified->at(i).size(); ++j)
		{
			// For each weight of that neuron
			for(unsigned int k = 0; k < modified->at(i).at(j).size(); ++k)
			{
				// Multiply solutions k-th element accordingly to coefficient
				modified->at(i).at(j).at(k) *= coefficient;
			}
		}
	}
}

void neuralFireflyStrategy::subtractThisSolutionFromGivenSolution(void *otherSolution, void *target)
{
	vector<layer>* difference;
	vector<layer>* minuend;

	if(hasProperType(otherSolution))  minuend = static_cast<vector<layer>*>(otherSolution);
	else return;

	if(hasProperType(target)) difference = static_cast<vector<layer>*>(target);
	else return;

	// For each layer of solution (minuend could be used instead of solution)
	for(unsigned int i = 0; i < solution->size(); ++i)
	{
		// Push layer to difference
		difference->push_back(layer());

		// For each neuron in that layer
		for(unsigned int j = 0; j < solution->at(i).size(); ++j)
		{
			// Push neuron to that layer in difference
			difference->at(i).push_back(neuron());

			// For each weight of that neuron
			for(unsigned int k = 0; k < solution->at(i).at(j).size(); ++k)
			{
				// Subtract that weight from the same weight in minuend
				double dif = minuend->at(i).at(j).at(k) - solution->at(i).at(j).at(k);

				// Push result to differences current neuron
				difference->at(i).at(j).push_back(dif);
			}
		}
	}
}

void neuralFireflyStrategy::addSolutionToThisSolution(void *otherSolution)
{
	vector<layer>* addend;

	if(hasProperType(otherSolution)) addend = static_cast<vector<layer>*>(otherSolution);
	else return;

	// For each layer of solution (addend could be used instead of solution)
	for(unsigned int i = 0; i < solution->size(); ++i)
	{
		// For each neuron in that layer
		for(unsigned int j = 0; j < solution->at(i).size(); ++j)
		{
			// For each weight of that neuron
			for(unsigned int k = 0; k < solution->at(i).at(j).size(); ++k)
			{
				// Add addend corresponding element to solution
				solution->at(i).at(j).at(k) += addend->at(i).at(j).at(k);
			}
		}
	}
}

bool neuralFireflyStrategy::hasProperType(void* target)
{
	// Check if target has expected type by dynamically casting
	try
	{
		static_cast<vector<layer>*>(target);
	}
	catch (bad_cast& bc)
	{
		cout << "Unexpected class type in firefly strategy: " << bc.what();

		return false;
	}

	return true;
}

// For displaying purposes.
string neuralFireflyStrategy::toString()
{
	string result = "Solution: \n";

	// For each layer
	for(unsigned int i = 0; i < solution->size(); ++i)
	{
		// For each neuron in that layer
		for (unsigned int j = 0; j < solution->at(i).size(); ++j)
		{
			result += "Layer " + to_string(i) + ", Neuron " + to_string(j) + ", Weights: ";

			// For each weight in that neuron
			for(unsigned int k = 0; k < solution->at(i).at(j).size(); ++k)
				result += to_string(solution->at(i).at(j).at(k)) + ", ";

			// Pop coma and space bar.
			result.pop_back();
			result.pop_back();

			result += "\n";
		}

		result += "\n";
	}

	return result;
}