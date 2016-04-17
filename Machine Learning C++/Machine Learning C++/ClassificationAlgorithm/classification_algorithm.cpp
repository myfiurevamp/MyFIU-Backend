//#include "../stdafx.h"
#include "classification_algorithm.h"

using namespace std;

ClassificationAlgorithm::ClassificationAlgorithm()
{
}


ClassificationAlgorithm::~ClassificationAlgorithm()
{
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

	int result;

	for (vector<string> record : records)
		if ((result = validateRecord(record)) <= -1)
			return result;

	return result = 0;
}
