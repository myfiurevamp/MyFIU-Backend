#pragma once
#include "ImpurityMeasure.h"
#include <vector>

using namespace std;

class Entropy:ImpurityMeasure
{

public:

	Entropy();
	Entropy(vector<float>);
	~Entropy();
	float calculate_impurity();

private: 
	vector<float> probabilities;

	float calculate_entropy();
	float calculate_conditional_entropy();



};