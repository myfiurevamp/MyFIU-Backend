#pragma once
#include "../include/impurity_measure.h"

class Entropy: public ImpurityMeasure
{

public:

	Entropy();
	~Entropy();
	float calculate_impurity(int attribute_index, relationTable table);
	int findBestInitalSplit(int class_label_index, relationTable table, float* attribute_impurity = NULL);
	int findBestSplitOnBranch(int class_label_index, int attribute_index_of_value, relationTable table, float* attribute_impurity = NULL);

private: 
	float calculate_entropy(int attribute_index, relationTable table);
	float calculate_conditional_entropy(int of_attribute_index, int on_attribute_index, relationTable table);
	float informationGain(float entropy1, float entropy2) { return entropy1 - entropy2; }


};