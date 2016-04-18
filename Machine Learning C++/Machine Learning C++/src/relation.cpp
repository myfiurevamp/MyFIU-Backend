#include "relation.h"

using namespace std;

relation::relation()
{
}

relation::~relation()
{
}

relation::relation(std::string _name, relationHeader _header, relationData _data)
{
	name = _name;
	header = _header;
	data = _data;
}

int relation::getIndexOfAttribute(string attribute_name)
{
	return header.getIndexOfAttribute(attribute_name);
}

auto relation::getAllAttributes()
{
	return header.all_attributes;
}

int relation::getNumOfAttributes()
{
	return header.size;
}

auto relation::getRecords()
{
	return data.records;
}

//const relationHeader& relation::getHeader()
//{
//	return header;
//}
//
//const relationData& relation::getData()
//{
//	return data;
//}
