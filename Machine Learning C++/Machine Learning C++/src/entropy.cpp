//#include "../../../../stdafx.h"
#include "../include/Entropy.h"
#include <math.h> 
#include <cfloat>

using namespace std;

Entropy::Entropy()
{
}

Entropy::~Entropy()
{
}

/* Caclulate the entropy of an attribute in a subset_of_records. */
float Entropy::calculate_entropy(int attribute_index, vector<vector<string>> subset_of_records)
{
	float entropy = 0.0;
	int num_of_attribute_value_contributions = 0;

	if (attribute_index == -1) // attribute does not exist, if less than 0
		return FLT_MAX;

	vector<string> attribute_values = relation_obj[attribute_index].values;

	if (attribute_values.size() <= 0) // no values
		return FLT_MAX;

	for (string attribute_value : attribute_values) // only works for nominal values?
	{
		int attribute_value_frequency = 0;
		float probability;

		for (vector<string> record : subset_of_records)
			if (record[attribute_index] == attribute_value)
				attribute_value_frequency++;

		if (attribute_value_frequency <= 0)
			continue;

		probability = attribute_value_frequency / (float) subset_of_records.size();
		entropy -= probability*log2(probability);
		num_of_attribute_value_contributions++;

	}

	/* If this is true, something went wrong...
	maybe 100% of the attribute values in subset_of_records are NULL?...
	*/
	if (num_of_attribute_value_contributions <= 0) 
		return FLT_MAX;

	return entropy;
}

/* Calculate the impurity (entropy) of an attribute. */
float Entropy::calculate_impurity(int attribute_index) 
{

	return calculate_entropy(attribute_index, relation_obj.getRecords()); // use function call simply for readability -- use all records

}


/* Calculate the expected conditional entropy of an attribute in relation to another attribute. */
float Entropy::calculate_conditional_entropy(int of_attribute_index, int on_attribute_index)
{
	float conditional_entropy = 0.0;

	if (of_attribute_index == -1) // attribute does not exist, if less than 0
		return FLT_MAX;

	if (on_attribute_index == -1) // attribute does not exist, if less than 0
		return FLT_MAX;

	vector<string> of_attribute_values = relation_obj[of_attribute_index].values;
	vector<string> on_attribute_values = relation_obj[on_attribute_index].values;

	if (of_attribute_values.size() <= 0) // no values
		return FLT_MAX;

	if (on_attribute_values.size() <= 0) // no values
		return FLT_MAX;

	for (string of_attribute_value : of_attribute_values) // only works for nominal values?
	{
		int of_attribute_value_frequency = 0;
		vector<vector<string>> of_attribute_value_records;

		/* Collect all records with of_attribute_value into of_attribute_value_records */
		for (vector<string> record : relation_obj.getRecords())
			if (record[of_attribute_index] == of_attribute_value)
			{
				of_attribute_value_frequency++;
				of_attribute_value_records.push_back(record);
			}

		/* For every on_attribute_value, iterate over collected records (of_attribute_value_records) to calculate conditional entropy */
		float on_attribute_entropy = calculate_entropy(on_attribute_index, of_attribute_value_records); 

		conditional_entropy += (of_attribute_value_frequency/ (float) relation_obj.getRecords().size()) * on_attribute_entropy;

	}
	
	return conditional_entropy;
}

int Entropy::findBestInitalSplit(int class_label_index, float* attribute_impurity)
{
	int relation_header_attribute_index = 0;
	int best_attribute_index = -1;
	float minimum_entropy = FLT_MAX;

	for (attribute relation_header_attribute: relation_obj.getAllAttributes()) {

		if (relation_header_attribute_index == class_label_index)
			continue;

		float conditional_entropy = calculate_conditional_entropy(relation_header_attribute_index, class_label_index);

		if (conditional_entropy < minimum_entropy)
		{
			minimum_entropy = conditional_entropy;
			best_attribute_index = relation_header_attribute_index;
			if(attribute_impurity != NULL)
				*attribute_impurity = conditional_entropy;
		}

		relation_header_attribute_index++;
	}

	return best_attribute_index;
}