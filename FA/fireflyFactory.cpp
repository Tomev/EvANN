#include "fireflyFactory.h"

fireflyFactory::fireflyFactory(double *stepSize, double *baseAttraction, double *absorption,
               i_distribution *distribution, void* fireflyStructure)
	: stepSize(stepSize), baseAttraction(baseAttraction), absorption(absorption),
	  distribution(distribution), fireflyStructure(fireflyStructure)
{}

fireflyFactory::fireflyFactory(double *stepSize, double *baseAttraction, double *absorption,
               i_distribution *distribution, neuralFireflyStrategy::topology* fireflyStructure)
	: stepSize(stepSize), baseAttraction(baseAttraction), absorption(absorption),
	  distribution(distribution), fireflyStructure(fireflyStructure)
{
	this->strategyType = neuralFirefly;
}

// Create proper firefly basing on current strategy type. Default is firefly with no strategy.
firefly fireflyFactory::createFirefly()
{
	switch(this->strategyType)
	{
		case neuralFirefly:
			return createNeuralFirefly();
		default:
			return firefly(NULL);
	}
}

firefly fireflyFactory::createNeuralFirefly()
{
	return firefly(
		new neuralFireflyStrategy(
			this->stepSize, this->baseAttraction, this->absorption,
			this->distribution, static_cast<neuralFireflyStrategy::topology*>(this->fireflyStructure)
		)
	);
}