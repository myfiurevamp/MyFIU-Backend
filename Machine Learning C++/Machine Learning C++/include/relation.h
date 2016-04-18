#pragma once
#include "relation_header.h"
#include "relation_data.h"

#include <string>

typedef struct relation {

public:
	relation();
	~relation();
	relation(std::string name, relationHeader header, relationData data);
	int getIndexOfAttribute(std::string attribute_name);
	auto getAllAttributes();
	int getNumOfAttributes();
	auto getRecords();

	attribute operator[](int i) { return header.all_attributes[i]; }

	/*const relationHeader& getHeader();
	const relationData& getData();*/

private:
	std::string name;
	relationHeader header;
	relationData data;

} relation;