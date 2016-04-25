#pragma once
#include "attribute_list.h"
#include <vector>

struct relationObj;

typedef struct relationHeader{

public:
	relationHeader();
	~relationHeader();
	relationHeader(attributeList _all_attributes);
	friend relationObj;

	attributeList all_attributes;
	int getIndexOfAttribute(std::string attribute_name);
	int getNumOfColumns();

private:
	std::string name;

} relationHeader;