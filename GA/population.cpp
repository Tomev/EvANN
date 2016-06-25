#include "population.h"


// For debug purposes.
string population::toString()
{
	string result = "";

	for(unsigned int i = 0; i < individuals.size(); ++i)
	{
		result += "Individual " + to_string(i) + ":\n";
		result += individuals.at(i).toString();
	}

	return result;
}