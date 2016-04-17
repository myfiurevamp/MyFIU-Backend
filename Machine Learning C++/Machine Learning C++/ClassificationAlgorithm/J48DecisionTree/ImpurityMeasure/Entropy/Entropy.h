#pragma once
#include "../impurity_measure.h"
//#include <vector>

class Entropy: public ImpurityMeasure
{

public:

	Entropy();
	Entropy(std::vector<float>);
	~Entropy();
	float calculate_impurity(int attribute_index);

private: 
	std::vector<float> probabilities;

	float calculate_entropy(int attribute_index, vector<vector<string>> subset_of_records);
	float calculate_conditional_entropy(int of_attribute_index, int on_attribute_index);

};