#pragma once
#include "../../../attribute.h"

class ImpurityMeasure 
{

public:

	ImpurityMeasure();
	~ImpurityMeasure();
	virtual float calculate_impurity(string attribute) = 0;

	void init(const std::vector<attribute>& dataset_header, const std::vector<std::vector<std::string>>& records, const std::string& class_label);


protected:
	std::string class_label;
	std::vector<attribute> dataset_header;
	std::vector<std::vector<std::string>> records;

private:

};