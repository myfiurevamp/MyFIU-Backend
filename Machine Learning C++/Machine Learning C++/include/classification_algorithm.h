#pragma once
#include "relation.h"
#include <string>

#define RECORD_SIZE_ERROR -1;
#define  ATTRIBUTE_TYPE_MISMATCH_ERROR -2;

	class ClassificationAlgorithm
	{
	public:
		ClassificationAlgorithm();
		~ClassificationAlgorithm();
		//TODO: create constructor to init relation and class label

		int setRelation(relation _relation_obj);
		void setClassLabel(std::string _class_label);
		virtual void predict(attribute class_attribute) = 0;
		//TODO: create function validaterelation() that checks for valid attribute names, repeated attribute names, etc.


		int class_label_index;
	/*	int num_of_records;
		int num_of_attributes;*/

	protected:
		relation relation_obj;
		std::string class_label;
		int validateRecord(std::vector<std::string> record);


	};
