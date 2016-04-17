#include "../../../../stdafx.h"
//#include "Entropy.h"
//#include <math.h> 
//#include <cfloat>

using namespace std;

Entropy::Entropy()
{
}

Entropy::Entropy(vector<float> _probabilities)
{
	probabilities = _probabilities;
}

Entropy::~Entropy()
{
}

/* Caclulate the entropy of an attribute in a subset_of_records. */
float Entropy::calculate_entropy(int attribute_index, vector<vector<string>> subset_of_records)
{
	float entropy = 0.0;

	if (attribute_index == -1) // attribute does not exist, if less than 0
		return FLT_MAX;

	vector<string> attribute_values = dataset_header[attribute_index].values;

	if (attribute_values.size() <= 0) // no values
		return FLT_MAX;

	for (string attribute_value : attribute_values) // only works for nominal values?
	{
		int attribute_value_frequency = 0;
		float probability;

		for (vector<string> record : subset_of_records)
			if (record[attribute_index] == attribute_value)
				attribute_value_frequency++;

		probability = attribute_value_frequency / (float) subset_of_records.size();

		entropy -= probability*log2(probability);

	}

	entropy = -entropy;

	return entropy;
}

/* Calculate the impurity (entropy) of an attribute. */
float Entropy::calculate_impurity(int attribute_index) 
{

	return calculate_entropy(attribute_index, records); // use function call simply for readability -- use all records

}


/* Calculate the expected conditional entropy of an attribute in relation to another attribute. */
float Entropy::calculate_conditional_entropy(int of_attribute_index, int on_attribute_index)
{
	int conditional_entropy = 0.0;

	vector<string> of_attribute_values = dataset_header[of_attribute_index].values;

	if (of_attribute_index == -1) // attribute does not exist, if less than 0
		return FLT_MAX;

	if (on_attribute_index == -1) // attribute does not exist, if less than 0
		return FLT_MAX;

	vector<string> of_attribute_values = dataset_header[of_attribute_index].values;
	vector<string> on_attribute_values = dataset_header[on_attribute_index].values;

	if (of_attribute_values.size() <= 0) // no values
		return FLT_MAX;

	if (on_attribute_values.size() <= 0) // no values
		return FLT_MAX;

	for (string of_attribute_value : of_attribute_values) // only works for nominal values?
	{
		int of_attribute_value_frequency = 0;
		vector<vector<string>> of_attribute_value_records;

		/* Collect all records with of_attribute_value into of_attribute_value_records */
		for (vector<string> record : records)
			if (record[of_attribute_index] == of_attribute_value)
			{
				of_attribute_value_frequency++;
				of_attribute_value_records.push_back(record);
			}

		/* For every on_attribute_value, iterate over collected records (of_attribute_value_records) to calculate conditional entropy */
		float on_attribute_entropy = calculate_entropy(on_attribute_index, of_attribute_value_records); 

		conditional_entropy += (of_attribute_value_frequency/ (float) records.size()) * on_attribute_entropy;

	}
	
	return conditional_entropy;
}

