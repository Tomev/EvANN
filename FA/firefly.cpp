#include "firefly.h"

using namespace std;

firefly::firefly() {}

firefly::firefly(i_fireflyStrategy *strategy) :
strategy(strategy)
{ }

void firefly::initialize()
{
	if(hasStrategy())	strategy->initialize();
	else return;
}

void firefly::flyTowards(void *otherFireflyPosition)
{
	if(hasStrategy())	strategy->flyTowards(otherFireflyPosition);
	else return;
}

void firefly::setIllumination(double value)
{
	this->illumination = value;
}

double firefly::getIllumination()
{
	return this->illumination;
}

void firefly::setEvaluationValue(double value)
{
	evaluationValue = value;
}

double firefly::getEvaluationValue()
{
	return evaluationValue;
}

void* firefly::getSolution()
{
	if(hasStrategy()) return strategy->getSolution();
	else return NULL;
}

void firefly::setSolution(void *newSolution)
{
	strategy->setSolution(newSolution);
}

std::string firefly::toString()
{
	if(hasStrategy()) return strategy->toString();
	else return "No strategy.";
}

void firefly::print()
{
	std::cout << this->toString() << std::endl;
}

bool firefly::hasStrategy()
{
	if(this->strategy == NULL)
	{
		cout << "[DEBUG] Firefly has no strategy.";
		return false;
	}

	return true;
}