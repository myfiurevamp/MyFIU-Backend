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


void ImpurityMeasure::setRelation(const relation& _relation_obj)
{
	relation_obj = _relation_obj;
	num_of_relation_attributes = relation_obj.getNumOfAttributes();
}


