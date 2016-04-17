//#include "../../../stdafx.h"
#include "impurity_measure.h"

using namespace std;

ImpurityMeasure::ImpurityMeasure()
{
}

//ImpurityMeasure::ImpurityMeasure(vector<attribute> _dataset_header, vector<vector<string>> _records, string _class_label)
//{
//	init(_dataset_header, _records, _class_label);
//}


ImpurityMeasure::~ImpurityMeasure()
{
}

void ImpurityMeasure::init(const vector<attribute>& _dataset_header, const vector<vector<string>>& _records/*, const string& _class_label*/)
{
	dataset_header = _dataset_header;
	records = _records;
	//class_label = _class_label;
	num_of_dataset_attributes = dataset_header.size();
}


