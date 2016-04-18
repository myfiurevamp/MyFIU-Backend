#pragma once
#include "../include/impurity_measure.h"
#include <vector>

class Entropy: public ImpurityMeasure
{

public:

	Entropy();
	~Entropy();
	float calculate_impurity(int attribute_index);
	int findBestInitalSplit(int class_label_index, float* attribute_impurity = NULL);


private: 
	float calculate_entropy(int attribute_index, std::vector<std::vector<std::string>> subset_of_records);
	float calculate_conditional_entropy(int of_attribute_index, int on_attribute_index);

};