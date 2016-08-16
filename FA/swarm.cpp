#include "swarm.h"

// Create and initialize fireflies swarm
swarm::swarm( double *stepSize, double *baseAttraction, double *absorption, unsigned int size,
              i_distribution *distribution, neuralFireflyStrategy::topology *fireflyStructure,
							neuralNet* nn)
{
	// Create proper factory
	fireflyFactory factory (stepSize, baseAttraction, absorption,
	                        distribution, fireflyStructure);

	// Create adequate objective function
	objectiveFunction = new neuralFireflyEvaluator(nn);

	double illumination = 0.0;

	// For each supposed firefly in swarm
	for(unsigned f = 0; f < size; ++f)
	{
		// Add new firefly to swarm
		fireflies.push_back(factory.createFirefly());
		firefly* newFirefly = &fireflies.at(fireflies.size()-1);

		// Set its illumination
		illumination = objectiveFunction->evaluate(newFirefly->getSolution());
		newFirefly->setIllumination(illumination);
	}
}

void swarm::findSolution()
{

}





