#pragma once
#include "../attribute.h"
#include <string>

#define RECORD_SIZE_ERROR -1;
#define  ATTRIBUTE_TYPE_MISMATCH_ERROR -2;

	class ClassificationAlgorithm
	{
	public:
		ClassificationAlgorithm();
		~ClassificationAlgorithm();
		//TODO: create constructor to init dataset and class label

		int validateRecord(std::vector<std::string> record);

		int initDataset(std::vector<attribute> _dataset_header, std::vector<std::vector<std::string>> _records);
		void initClassLabel(std::string _class_label);
		virtual void predict(attribute class_attribute) = 0;
		//TODO: create function validateDataset() that checks for valid attribute names, repeated attribute names, etc.


		int class_label_index;
	/*	int num_of_records;
		int num_of_attributes;*/

	protected:
		std::vector<attribute> dataset_header;
		std::vector<std::vector<std::string>> records;
		int getAttributeIndex(std::string string_attribute);
		std::string class_label;
		
		


	};
