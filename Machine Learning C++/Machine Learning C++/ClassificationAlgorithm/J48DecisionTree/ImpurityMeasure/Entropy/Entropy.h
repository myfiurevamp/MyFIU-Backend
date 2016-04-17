#pragma once
#include "../impurity_measure.h"
//#include <vector>

class Entropy: public ImpurityMeasure
{

public:

	Entropy();
	Entropy(std::vector<float>);
	~Entropy();
	float calculate_impurity(string attribute);

private: 
	std::vector<float> probabilities;

	float calculate_entropy();
	float calculate_conditional_entropy();



};