#include "swarm.h"

// Create and initialize fireflies swarm
swarm::swarm( double *stepSize, double *baseAttraction, double *absorption, unsigned int size,
              i_distribution *distribution, neuralNet* nn)
{
	// Create proper factory
	fireflyFactory factory (stepSize, baseAttraction, absorption,
	                        distribution, nn->getTopology());

	// Create adequate objective function
	objectiveFunction = new neuralWessingerEvaluator(nn);

	double illumination;

	// For each supposed firefly in swarm
	for(unsigned f = 0; f < size; ++f)
	{
		// Add new firefly to swarm
		fireflies.push_back(factory.createFirefly());
		firefly* newFirefly = &fireflies.at(fireflies.size()-1);

		// Initialize it
		newFirefly->initialize();

		// Set its illumination
		illumination = objectiveFunction->evaluate(newFirefly->getSolution());
		newFirefly->setIllumination(illumination);
	}

	/* Find current brightest firefly (worst firefly) and
	 * remember it's illumination value for normalization
	 * purposes. */
	highestKnownError = findBrightestFirefly()->getIllumination();

	normalizeSwarm();
}

void swarm::normalizeSwarm()
{
	// For each firefly in swarm
	for(unsigned int f = 0; f < fireflies.size(); ++f)
	{
		// Normalize its illumination
		firefly* fly = &fireflies.at(f);
		fly->setIllumination(normalize(fly->getIllumination()));
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
					if(newPositionError > highestKnownError) highestKnownError = newPositionError;

					// Set normalized error as new firefly illumination
					fly_i->setIllumination(normalize(newPositionError));

					//cout << "Normal move" << endl;
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
        if(newPositionError > highestKnownError) highestKnownError = newPositionError;

        // Set normalized error as new firefly illumination
        fly_i->setIllumination(normalize(newPositionError));

				//cout << "Random move" << endl;
			}
		}
		//cout << "Iteration " + to_string(iteration) << endl;
		cout << ".";
	}

	cout << endl;

	bestFirefly = findBrightestFirefly();
  cout << "Biggest error = " << highestKnownError << endl;
	cout << "End error = " << objectiveFunction->evaluate(bestFirefly->getSolution());
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





