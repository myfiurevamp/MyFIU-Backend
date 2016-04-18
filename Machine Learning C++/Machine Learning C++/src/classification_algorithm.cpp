//#include "../stdafx.h"
#include "../include/classification_algorithm.h"

using namespace std;

ClassificationAlgorithm::ClassificationAlgorithm()
{
}


ClassificationAlgorithm::~ClassificationAlgorithm()
{
}

void ClassificationAlgorithm::setClassLabel(std::string _class_label)
{
	class_label = _class_label;
	class_label_index = relation_obj.getIndexOfAttribute(_class_label);
}

int ClassificationAlgorithm::validateRecord(vector<string> record) // private
{
	int required_num_of_attributes = relation_obj.getNumOfAttributes();

	if (record.size() != required_num_of_attributes)
		return RECORD_SIZE_ERROR;

	for (unsigned int i = 0; i < required_num_of_attributes; i++)

		if (relation_obj[i].type == attribute_type::NUMERIC)
		{
			try 
			{
				stof(record[i]); // parse number
			}
			catch (invalid_argument e) {
				return ATTRIBUTE_TYPE_MISMATCH_ERROR;
			}
		}
		else if (relation_obj[i].type == attribute_type::DATE)
		{
			// implement
		}

	return 0;
}

int ClassificationAlgorithm::setRelation(relation _relation_obj)
{
	relation_obj = _relation_obj;

	//num_of_attributes = relation_header.size();
	//num_of_records = records.size();

	int result;

	for (vector<string> record : relation_obj.getRecords())
		if ((result = validateRecord(record)) <= -1)
			return result;

	return result = 0;
}

