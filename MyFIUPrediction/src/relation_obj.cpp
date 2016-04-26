#include "../include/relation_obj.h"

using namespace std;

relationObj::relationObj()
{
}

relationObj::~relationObj()
{
}

relationObj::relationObj(std::string _name, relationHeader _header, relationTable _table)
{
	header = _header;
	header.name = _name;
	table = _table;
}

int relationObj::getIndexOfAttribute(string attribute_name)
{
	return header.getIndexOfAttribute(attribute_name);
}

attributeList relationObj::getAllAttributes()
{
	return header.all_attributes;
}

int relationObj::getNumOfAttributes()
{
	return header.getNumOfColumns();
}

int relationObj::getNumOfRecords()
{
	return table.getNumOfRows();
}

void relationObj::setTable(relationTable _table)
{
	table = _table;
}

relationTable relationObj::getTable()
{
	return table;
}

relationTable relationObj::selectAll(int attribute_index, std::string attribute_value_name)
{
	return table.selectAll(attribute_index, attribute_value_name);
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
