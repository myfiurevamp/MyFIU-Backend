//#include "../../../../stdafx.h"
#include "../include/Entropy.h"
#include <math.h> 
#include <cfloat>
//#include <vector>


using namespace std;

Entropy::Entropy()
{
}

Entropy::~Entropy()
{
}

/* Caclulate the entropy of an attribute in a subset_of_records. */
float Entropy::calculate_entropy(int attribute_index, relationTable table)
{
	float entropy = 0.0;
	int num_of_attribute_value_contributions = 0;

	attribute selected_attribute = relation_header.all_attributes[attribute_index];

	if (selected_attribute.getNumOfValues() <= 0) // no values
		return FLT_MAX;

	tableColumn selected_column = table.getColumn(attribute_index);

	for (string attribute_value : selected_attribute) // only works for nominal values?
	{
		int attribute_value_frequency = 0;
		float probability;

		for(string value: selected_column)
			if (value == attribute_value)
				attribute_value_frequency++;

		if (attribute_value_frequency <= 0)
			continue;

		probability = attribute_value_frequency / (float) table.getNumOfRows();
		if (probability != 0.0)
			entropy -= probability*log2(probability);
		num_of_attribute_value_contributions++;

	}

	/* 
	If this is true, something went wrong...
	maybe 100% of the attribute values in subset_of_records are NULL?...
	*/
	if (num_of_attribute_value_contributions <= 0) 
		return FLT_MAX;

	return entropy;
}

/* Calculate the impurity (entropy) of an attribute. */
float Entropy::calculate_impurity(int attribute_index, relationTable table)
{

	return calculate_entropy(attribute_index, table); // use function call simply for readability -- use all records

}


/* Calculate the expected conditional entropy of an attribute in relation to another attribute. */
float Entropy::calculate_conditional_entropy(int of_attribute_index, int on_attribute_index, relationTable table)
{
	float conditional_entropy = 0.0;

	attribute of_attribute = relation_header.all_attributes[of_attribute_index];
	attribute on_attribute = relation_header.all_attributes[on_attribute_index];

	if (of_attribute.getNumOfValues() <= 0) // no values
		return FLT_MAX;

	if (on_attribute.getNumOfValues() <= 0) // no values
		return FLT_MAX;

	for (string of_attribute_value : of_attribute) // only works for nominal values?
	{
		int of_attribute_value_frequency = 0;
		relationTable of_attribute_value_records;

		/* Collect all records with of_attribute_value into of_attribute_value_records */
		for (tableRow record : table)
			if (record[of_attribute_index] == of_attribute_value)
			{
				of_attribute_value_frequency++;
				of_attribute_value_records.push_back(record);
			}

		/* For every on_attribute_value, iterate over collected records (of_attribute_value_records) to calculate conditional entropy */
		float on_attribute_entropy = calculate_entropy(on_attribute_index, of_attribute_value_records); 

		conditional_entropy += (of_attribute_value_frequency/ (float) table.getNumOfRows()) * on_attribute_entropy;

	}
	
	return conditional_entropy;
}

int Entropy::findBestInitalSplit(int class_label_index, relationTable table, float* attribute_impurity)
{
	int relation_header_attribute_index = 0;
	int best_attribute_index = -1;
	float best_attribute_entropy = FLT_MAX;

	float class_label_entropy = calculate_entropy(class_label_index, table);
	float max_information_gain = 0;

	attributeList relation_attribute_list = relation_header.all_attributes;

	for (attribute relation_header_attribute: relation_attribute_list) {

		if (isIgnoredAttribute(relation_header_attribute_index))
		{
			relation_header_attribute_index++;
			continue;
		}

		if (relation_header_attribute_index == class_label_index)
		{
			relation_header_attribute_index++;
			continue;
		}

		if(relation_header_attribute.is_unique == true)
		{
			relation_header_attribute_index++;
			continue;
		}
			
		float conditional_entropy = calculate_conditional_entropy(relation_header_attribute_index, class_label_index, table);

		float new_info_gain = informationGain(class_label_entropy, conditional_entropy);
		float old_info_gain = informationGain(class_label_entropy, best_attribute_entropy);

		if (new_info_gain > old_info_gain)
		{
			max_information_gain = new_info_gain;
			best_attribute_entropy = conditional_entropy;
			best_attribute_index = relation_header_attribute_index;
			if(attribute_impurity != NULL)
				*attribute_impurity = conditional_entropy;
		}

		relation_header_attribute_index++;

		if (conditional_entropy == 0.0)
			break;
	}

	//cout << "Max information Gain: " <<  max_information_gain << endl;
	ignored_attribute_indexes.push_back(best_attribute_index);
	return best_attribute_index;
}

/*
Precondition: Assumes all appropriate rows have been selected in table.
*/
int Entropy::findBestSplitOnBranch(int class_label_index, int attribute_index_of_value, relationTable table, float* attribute_impurity)
{
	int relation_header_attribute_index = 0;
	int best_attribute_index = -1;
	float best_attribute_entropy = FLT_MAX;

	float branch_entropy = calculate_entropy(class_label_index, table); // assumes all rows with outlook="sunny" are selected
	float max_information_gain = 0;

	attributeList relation_attribute_list = relation_header.all_attributes;

	for (attribute relation_header_attribute : relation_attribute_list) {

		if (isIgnoredAttribute(relation_header_attribute_index))
		{
			relation_header_attribute_index++;
			continue;
		}

		if (relation_header_attribute_index == class_label_index || relation_header_attribute_index == attribute_index_of_value)
		{
			relation_header_attribute_index++;
			continue;
		}

		if (relation_header_attribute.is_unique == true)
		{
			relation_header_attribute_index++;
			continue;
		}

		float conditional_entropy = calculate_conditional_entropy(relation_header_attribute_index, class_label_index, table);

		float new_info_gain = informationGain(branch_entropy, conditional_entropy);
		float old_info_gain = informationGain(branch_entropy, best_attribute_entropy);

		if (new_info_gain > old_info_gain)
		{
			max_information_gain = new_info_gain;
			best_attribute_entropy = conditional_entropy;
			best_attribute_index = relation_header_attribute_index;
			if (attribute_impurity != NULL)
				*attribute_impurity = conditional_entropy;
		}

		relation_header_attribute_index++;

		if (conditional_entropy == 0.0)
			break;
	}

	//cout << "Max information Gain: " << max_information_gain << endl;
	ignored_attribute_indexes.push_back(best_attribute_index);
	return best_attribute_index;
}
