#include "swarm.h"

// Create and initialize fireflies swarm
swarm::swarm( double *stepSize, double *baseAttraction, double *absorption,
              unsigned int size, unsigned int iterations,
              i_distribution *distribution, neuralNet* nn) :
	iterations(iterations)
{
	// Create proper factory
	fireflyFactory factory (stepSize, baseAttraction, absorption,
	                        distribution, nn->getTopology());

	// Create adequate objective function
	objectiveFunction = new alternativeNeuralWessingersEvaluator(nn);

	double evaluationValue;

	// For each supposed firefly in swarm
	for(unsigned f = 0; f < size; ++f)
	{
		// Add new firefly to swarm
		fireflies.push_back(factory.createFirefly());
		firefly* newFirefly = &fireflies.at(fireflies.size()-1);

		// Initialize it
		newFirefly->initialize();

		// Evaluate it
		evaluationValue = objectiveFunction->evaluate(newFirefly->getSolution());
		newFirefly->setEvaluationValue(evaluationValue);

		// Check if its error is highest so far and update if so
		if(evaluationValue > highestKnownError)
			highestKnownError = evaluationValue;
	}

	// Set proper normalized evaluation (illumination) for whole swarm
	normalizeSwarm();

	// Initialize and remember current best solution
	bestFirefly = findBrightestFirefly();
	bestSolutionHolder = factory.createFirefly();
	bestSolutionHolder.initialize();
	bestSolutionHolder.setSolution(bestFirefly->getSolution());
}

void swarm::normalizeSwarm()
{
	// For each firefly in swarm
	for(unsigned int f = 0; f < fireflies.size(); ++f)
	{
		// Normalize its illumination
		firefly* fly = &fireflies.at(f);
		fly->setIllumination(normalize(fly->getEvaluationValue()));
	}
}

double swarm::normalize(double value)
{
	if(highestKnownError > 0) return 1 - value / highestKnownError;
	else return 1;
}

// TODO when moving firefly add method to do all the moving logic
// eg. move ff, update its fitness, check for highestKnownError...

void swarm::findSolution()
{
	// DEBUG
	bestFirefly = findBrightestFirefly();
	cout << "Start error = " << objectiveFunction->evaluate(bestFirefly->getSolution()) << endl;
  cout << "Biggest error = " << highestKnownError << endl;
	// END DEBUG

	// For each iteration
	for(unsigned int iteration = 0; iteration < iterations; ++iteration)
	{
		// For each both fireflies
		for(unsigned int i = 0; i < fireflies.size(); ++i)
		{
			firefly* fly_i = &fireflies.at(i);
			bool hasMoved = false;

			for(unsigned int j = 0; j < fireflies.size(); ++j)
			{
				firefly* fly_j = &fireflies.at(j);

				// If fly_j shines brighter
				if(fly_j->getIllumination() > fly_i->getIllumination())
				{
					// Move firefly i towards firefly j
					fly_i->flyTowards(fly_j->getSolution());
					hasMoved = true;

					// Evaluate new solution
					double newPositionError = objectiveFunction->evaluate(fly_i->getSolution());

					// Update biggest error if newPositionError is bigger
					if(newPositionError > highestKnownError)
					{
						highestKnownError = newPositionError;

						// Normalize swarm according to new error
						normalizeSwarm();
					}

					// Set normalized error as new firefly illumination
					fly_i->setIllumination(normalize(newPositionError));

					bestFirefly = findBrightestFirefly();
					bestSolutionHolder.setSolution(bestFirefly->getSolution());
				}
			}

			// Move firefly in random direction if it didn't move
			if(!hasMoved)
			{
				// TODO Find out why doesn't it work
				fly_i->flyTowards(NULL);

        // Evaluate new solution
        double newPositionError = objectiveFunction->evaluate(fly_i->getSolution());

        // Update biggest error if newPositionError is bigger
        if(newPositionError > highestKnownError)
        {
	        highestKnownError = newPositionError;

	        // Normalize swarm according to new error
	        normalizeSwarm();
        }

        // Set normalized error as new firefly illumination
        fly_i->setIllumination(normalize(newPositionError));

				bestFirefly = findBrightestFirefly();
				bestSolutionHolder.setSolution(bestFirefly->getSolution());
			}
		}
		cout << ".";
	}

	cout << endl;

  cout << "Biggest error = " << highestKnownError << endl;
	cout << "End error = " << objectiveFunction->evaluate(bestSolutionHolder.getSolution()) << endl;
}

firefly* swarm::findBrightestFirefly()
{
	// Set first firefly as the brightest
	firefly* brightest = &fireflies.at(0);

	// For each other firefly in swarm
	for(unsigned int f = 1; f < fireflies.size(); ++f)
	{
		// Update brightest firefly if another fly is brightest than current the brightest
		if(brightest->getIllumination() < fireflies.at(f).getIllumination())
			brightest = &fireflies.at(f);
	}

	return brightest;
}

void* swarm::getResult()
{
	return bestFirefly->getSolution();
}





