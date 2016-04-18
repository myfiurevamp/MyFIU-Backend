#include "..\include\relation_data.h"

using namespace std;

struct relationData;

relationData::relationData()
{
}

relationData::~relationData()
{
}

relationData::relationData(vector<vector<string>> _records)
{
	records = _records;
	size = records.size();

}
//
//int relationData::getSize()
//{
//	return size;
//}
//
//vector<vector<string>> relationData::getRecords()
//{
//	return records;
//}
