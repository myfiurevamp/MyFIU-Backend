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
	class_label_index = relation_obj.getIndexOfAttribute(class_label);
}

int ClassificationAlgorithm::validateRecord(tableRow record) // private
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

int ClassificationAlgorithm::setRelation(relationObj _relation_obj)
{
	//num_of_attributes = relation_header.size();
	//num_of_records = records.size();

	int result;

	relation_obj = _relation_obj; // only used for validating records; validate records after accounting for non-nominal values?

	relationTable _relation_obj_table = _relation_obj.getTable();

	for (tableRow record : _relation_obj_table)
		if ((result = validateRecord(record)) <= -1)
			return result;

	/* Accounts for non-nominal values */
	attributeList attr_list =  _relation_obj.getAllAttributes();

	vector<attribute> new_attr_vector;

	int i = 0;
	for (attribute attr : attr_list)
	{
		if (attr.type != attribute_type::NOMINAL)
		{
			tableColumn col = _relation_obj_table.getColumn(i);

			if (col.hasDistinctValues() == true)
				attr.setUniqueness(true);
			
			for (string value : col)
			{
				/* If value is not in attribute.all_values, add it */
				if (find(attr.all_values.begin(), attr.all_values.end(), value) == attr.all_values.end())
						attr.all_values.push_back(value);
			}
		}
		
		new_attr_vector.push_back(attr);
		i++;
	}

	attributeList new_attr_list = attributeList(new_attr_vector.begin(), new_attr_vector.end());
	relationHeader new_header = relationHeader(new_attr_list);
	relation_obj = relationObj(_relation_obj.getName(), new_header, _relation_obj_table);

	return result = 0;
}

