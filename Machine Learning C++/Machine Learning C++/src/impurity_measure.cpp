//#include "../../../stdafx.h"
#include "../include/impurity_measure.h"

using namespace std;

ImpurityMeasure::ImpurityMeasure()
{
}

//ImpurityMeasure::ImpurityMeasure(vector<attribute> _relation_header, vector<vector<string>> _records, string _class_label)
//{
//	init(_relation_header, _records, _class_label);
//}


ImpurityMeasure::~ImpurityMeasure()
{
}



void ImpurityMeasure::setRelationHeader(relationHeader _relation_header)
{
	relation_header = _relation_header;
}

bool ImpurityMeasure::isIgnoredAttribute(int attribute_index)
{
	if (find(ignored_attribute_indexes.begin(), ignored_attribute_indexes.end(), attribute_index) != ignored_attribute_indexes.end())
		return true;
	else
		return false;

}

