#pragma once
#include "relation.h"

class ImpurityMeasure 
{

public:

	ImpurityMeasure();
	~ImpurityMeasure();
	virtual float calculate_impurity(int attribute_index) = 0; // calculate for any attribute, most likely will be for class_label
	virtual int findBestInitalSplit(int class_label_index, float* attribute_impurity = NULL) = 0;
	void setRelation(const relation& _relation_obj);

protected:
	//std::string class_label;
	relation relation_obj;
	int num_of_relation_attributes;

private:

};