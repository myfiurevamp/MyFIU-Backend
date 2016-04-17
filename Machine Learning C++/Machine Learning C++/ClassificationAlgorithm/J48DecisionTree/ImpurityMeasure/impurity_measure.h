#pragma once
#include "../../../attribute.h"

class ImpurityMeasure 
{

public:

	ImpurityMeasure();
	~ImpurityMeasure();
	virtual float calculate_impurity(int attribute_index) = 0;

	void init(const std::vector<attribute>& dataset_header, const std::vector<std::vector<std::string>>& records/*, const std::string& class_label*/);

protected:
	//std::string class_label;
	std::vector<attribute> dataset_header;
	int num_of_dataset_attributes;
	std::vector<std::vector<std::string>> records;

private:

};