#pragma once
#include "attribute.h"
#include <vector>

struct relation;

typedef struct relationHeader{

public:
	relationHeader();
	~relationHeader();
	relationHeader(std::vector<attribute> _all_attributes);
	friend relation;

private:
	int size;
	std::vector<attribute> all_attributes;
	int getIndexOfAttribute(std::string attribute_name);

} relationHeader;