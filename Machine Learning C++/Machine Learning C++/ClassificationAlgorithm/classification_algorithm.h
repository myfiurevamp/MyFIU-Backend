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

		int validateRecord(std::vector<std::string> record);

		int initDataset(std::vector<attribute> _dataset_header, std::vector<std::vector<std::string>> _records);
		virtual void predict(attribute class_attribute) = 0;

	protected:
		std::vector<attribute> dataset_header;
		std::vector<std::vector<std::string>> records;


	};
