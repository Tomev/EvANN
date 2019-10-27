#include "swarm.h"
#include "../ObjectiveFunctions/Normalizers/basicNormalizer.h"

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
	_normalizer = std::make_shared<basicNormalizer>();

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
	updateBestSolutionHolder(bestFirefly);
}

void swarm::normalizeSwarm()
{
	// For each firefly in swarm
	for(auto fly : fireflies)
	{
		// Normalize its illumination
		fly.setIllumination(normalize(fly.getEvaluationValue()));
	}
}

double swarm::normalize(double value)
{
	return _normalizer->normalize(value);
}

void swarm::findSolution()
{
	// DEBUG
	bestFirefly = findBrightestFirefly();
	cout << "Start error = " << objectiveFunction->evaluate(bestFirefly->getSolution()) << endl;
  cout << "Biggest error = " << highestKnownError << endl;
  cout << "Standard derivative = " << countStandardDerivative() << endl;
	// END DEBUG

	// For each iteration
	for(unsigned int iteration = 0; iteration < iterations; ++iteration)
	{
		// For each both fireflies
		for(unsigned int i = 0; i < fireflies.size(); ++i)
    {
		  firefly* fly_i = &(fireflies[i]);
			bool hasMoved = false;

			for(auto fly_j : fireflies)
			{
				// If fly_j shines brighter
				if(fly_j.getIllumination() > fly_i->getIllumination())
        {
          // Move firefly if update necessary swarm data
          moveFFAndUpdateSwarmData(fly_i, &fly_j);
          hasMoved = true;
        }
			}

			// Move firefly in random direction if it didn't move
			//if(!hasMoved) moveFFAndUpdateSwarmData(fly_i, nullptr);
      if(!hasMoved) moveFFAndUpdateSwarmData(fly_i, nullptr);
		}

		if(fmod(iteration, iterations / 10) == 0) cout << "Iteration " << iteration << ": " << countFitnessSum() << endl;
	}

	cout << endl;

  cout << "Biggest error = " << highestKnownError << endl;
	cout << "End error = " << objectiveFunction->evaluate(bestSolutionHolder.getSolution()) << endl;
  cout << "Standard derivative = " << countStandardDerivative() << endl;
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
	return bestSolutionHolder.getSolution();
}

void swarm::updateBestSolutionHolder(firefly* ff)
{
	bestSolutionHolder.setSolution(ff->getSolution());
	bestSolutionHolder.setEvaluationValue(ff->getEvaluationValue());
  bestSolutionHolder.setIllumination(ff->getIllumination());
}

void swarm::moveFFAndUpdateSwarmData(firefly* ff, firefly* target)
{
  // Move firefly
  if(target == nullptr) ff->flyTowards(target);
  else ff->flyTowards(target->getSolution());

  // Evaluate new position of ff
  ff->setEvaluationValue(objectiveFunction->evaluate(ff->getSolution()));
  ff->setIllumination(normalize(ff->getEvaluationValue()));

  // Update biggest error if newPositionError is bigger
  if(ff->getEvaluationValue() > highestKnownError)
  {
    highestKnownError = ff->getEvaluationValue();

    // Normalize swarm according to new error
    normalizeSwarm();
  }

  // Compare moved firefly with current best
  if(ff->getIllumination() > bestFirefly->getIllumination())
  {
    // If it's better remember it
    bestFirefly = ff;

    // Check if it's better than current overall best
    if(bestFirefly->getIllumination() > bestSolutionHolder.getIllumination() )
    {
      // Update best if so
      updateBestSolutionHolder(bestFirefly);
    }
  }
}

double swarm::countFitnessSum()
{
  double sum = 0.0;

  // For each firefly add it's fitness to sum
  for(auto f : fireflies)  sum += f.getIllumination();

  return sum;
}

double swarm::countVariation()
{
  double variation = 0.0;
  double average = countFitnessSum() / fireflies.size();;

  // For each firefly add element basing on it's fitness to variation
  for(auto fly : fireflies) variation += pow(fly.getIllumination() - average ,2);

  variation /= fireflies.size();

  return variation;
}

double swarm::countStandardDerivative()
{
  return sqrt(countVariation());
}