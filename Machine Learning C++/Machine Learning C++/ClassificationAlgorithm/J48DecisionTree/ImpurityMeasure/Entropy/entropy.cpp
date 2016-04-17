#include "../../../../stdafx.h"
//#include "Entropy.h"
//#include <math.h> 
//#include <cfloat>

using namespace std;

Entropy::Entropy()
{
}

Entropy::Entropy(vector<float> _probabilities)
{
	probabilities = _probabilities;
}

Entropy::~Entropy()
{
}

/* Calculate the impurity (entropy) of an attribute. */
float Entropy::calculate_impurity(string attribute) 
{
	return calculate_entropy(); // use function call simply for readability

}

/* Caclulate the entropy of an attribute. */
float Entropy::calculate_entropy()
{
	float entropy = 0.0;
	float probability;

	if (probabilities.size() == 0)
		return FLT_MAX; //macro constant for maximum finite float value

	for (auto iterator = probabilities.begin(); iterator != probabilities.end(); iterator++) {
		probability = *iterator;
		entropy -= probability*log2(probability);
	}

	return entropy;
}

/* Calculate the expected conditional entropy of an attribute in relation to another attribute. */
float Entropy::calculate_conditional_entropy()
{
	return FLT_MAX;
}

