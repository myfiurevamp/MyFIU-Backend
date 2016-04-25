#pragma once
#include "relation_obj.h"

class ImpurityMeasure 
{

public:

	ImpurityMeasure();
	~ImpurityMeasure();
	ImpurityMeasure(relationHeader _relation_header) { setRelationHeader(_relation_header); }
	virtual float calculate_impurity(int attribute_index, relationTable table) = 0; // calculate for any attribute, most likely will be for class_label
	virtual int findBestInitalSplit(int class_label_index, relationTable table, float* attribute_impurity = NULL) = 0;
	virtual int findBestSplitOnBranch(int class_label_index, int attribute_index_of_value, relationTable table, float* attribute_impurity = NULL) = 0;
	void setRelationHeader(relationHeader _relation_header);
	bool isIgnoredAttribute(int attribute_index);

	template <class InputIterator> 
	void setIgnoredAttributes(InputIterator first, InputIterator last) // make a clearIgnoredAttributes function?
	{
		for (InputIterator it = first; it != last; it++)
		{
			int ignored_attribute_index = *it;
			ignored_attribute_indexes.push_back(ignored_attribute_index);
		}
	}
	//float getClassLabelImpurity();

protected:
	//virtual float calculateAttributeValueImpurity(std::string branch_name, relationTable table) = 0; 
	std::vector<int> ignored_attribute_indexes;
	relationHeader relation_header; //only need to know header. supply table to each method as argument



private:

};