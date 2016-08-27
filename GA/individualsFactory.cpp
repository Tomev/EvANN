#include "individualsFactory.h"

individualsFactory::individualsFactory(neuralNet *nn, i_distribution *distribution) :
nn(nn), distribution(distribution)
{
  individualStrategyId = neuralIndividual;
}

individual individualsFactory::createIndividual()
{
  switch(individualStrategyId)
  {
    case neuralIndividual:
      return createNeuralIndividual();
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
      offspring = individual(
          new neuralIndividualStrategy(
              nn->getTopology(),
              distribution
          )
      );
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
  return individual(
      new neuralIndividualStrategy(
          nn->getTopology(), distribution
      )
  );
}
