#include <iostream>
#include "individualsFactory.h"

individualsFactory::individualsFactory(neuralNet *nn, i_distribution *distribution) :
nn(nn), distribution(distribution)
{
  individualStrategyId = RSSRoll;
}

individual individualsFactory::createIndividual()
{
  switch(individualStrategyId)
  {
    case neuralIndividual:
      return createNeuralIndividual();
    case RSSRoll:
      return createRSSRollIndividual();
    case RSSBounce:
      return createRSSBounceIndividual();
    default:
      return individual(NULL);
  }
}

individual individualsFactory::createIndividual(individual *p1, individual *p2)
{
  individual offspring(NULL);

  switch(individualStrategyId)
  {
    case neuralIndividual:
      offspring = createNeuralIndividual();
      break;
    case RSSRoll:
      offspring = createRSSRollIndividual();
      break;
    case RSSBounce:
      offspring = createRSSBounceIndividual();
      break;
    default:
      offspring = individual(NULL);
      break;
  }

  p1->cross(p2->getSolution(), &offspring);

  return offspring;
}

individual individualsFactory::createNeuralIndividual()
{
  return individual(new neuralIndividualStrategy(nn->getTopology(), distribution));
}

individual individualsFactory::createRSSBounceIndividual()
{
  return individual(new RSSBounceIndividualStrategy(nn->getTopology(), distribution));
}

individual individualsFactory::createRSSRollIndividual()
{
  return individual(new RSSRollIndividualStrategy(nn->getTopology(), distribution));
}
