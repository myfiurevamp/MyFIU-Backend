#pragma once
#include "relation_header.h"
#include "relation_table.h"

#include <string>

typedef struct relationObj {

public:
	relationObj();
	~relationObj();
	relationObj(std::string name, relationHeader header, relationTable table);
	int getIndexOfAttribute(std::string attribute_name);
	std::string getName() { return header.name; }
	attributeList getAllAttributes();
	int getNumOfAttributes();
	int getNumOfRecords();
	void setTable(relationTable _table);
	relationHeader getHeader() { return header; }
	relationTable getTable();
	relationTable selectAll(int attribute_index, std::string attribute_value_name);

	attribute operator[](int index) { return getAllAttributes()[index]; }
	std::string getAttributeName(int index) { return getAllAttributes()[index].name; }


private:
	relationHeader header;
	relationTable table;

} relationObj;