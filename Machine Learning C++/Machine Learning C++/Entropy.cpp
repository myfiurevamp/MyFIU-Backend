#include "Entropy.h"
#include <math.h> 
#include <cfloat>

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

float Entropy::calculate_impurity()
{
	float impurity = 0.0;
	float probability;

	if (probabilities.size == 0)
		return FLT_MAX; //macro constant for maximum finite float value

	for (auto iterator = probabilities.begin(); iterator != probabilities.end(); iterator++) {
		probability = *iterator;
		impurity -= probability*log2(probability);
	}

	return impurity;
}
