//#include "../stdafx.h"
#include "classification_algorithm.h"

using namespace std;

ClassificationAlgorithm::ClassificationAlgorithm()
{
}


ClassificationAlgorithm::~ClassificationAlgorithm()
{
}

void ClassificationAlgorithm::initClassLabel(std::string _class_label)
{
	class_label = _class_label;
	class_label_index = getAttributeIndex(_class_label);
}

int ClassificationAlgorithm::validateRecord(vector<string> record) // private
{
	int required_num_of_attributes = dataset_header.size();

	if (record.size() != required_num_of_attributes)
		return RECORD_SIZE_ERROR;

	for (unsigned int i = 0; i < dataset_header.size(); i++)

		if (dataset_header[i].type == attribute_type::NUMERIC)
		{
			try 
			{
				stof(record[i]); // parse number
			}
			catch (invalid_argument e) {
				return ATTRIBUTE_TYPE_MISMATCH_ERROR;
			}
		}
		else if (dataset_header[i].type == attribute_type::DATE)
		{
			// implement
		}

	return 0;
}

int ClassificationAlgorithm::initDataset(vector<attribute> _dataset_header, vector<vector<string>> _records)
{
	dataset_header = _dataset_header;
	records = _records;

	//num_of_attributes = dataset_header.size();
	//num_of_records = records.size();

	int result;

	for (vector<string> record : records)
		if ((result = validateRecord(record)) <= -1)
			return result;

	return result = 0;
}

int ClassificationAlgorithm::getAttributeIndex(string string_attribute)
{
	int i = 0;

	for (attribute dataset_header_attribute : dataset_header)
	{
		if (dataset_header_attribute.name == string_attribute)
			return i;
		i++;
	}

	return -1;
}
