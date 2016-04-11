#pragma once
class ImpurityMeasure 
{

public:
	ImpurityMeasure();
	~ImpurityMeasure();
	virtual float calculate_impurity() = 0;


};