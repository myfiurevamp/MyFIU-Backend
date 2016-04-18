#include "../include/relation_header.h"

using namespace std;

struct relationHeader;

relationHeader::relationHeader()
{
}

relationHeader::~relationHeader()
{
}

relationHeader::relationHeader(vector<attribute> _all_attributes)
{
	all_attributes = _all_attributes;
	size = all_attributes.size();
}

int relationHeader::getIndexOfAttribute(std::string attribute_name)
{
	int index_of_attribute = 0;

	for (attribute relation_attribute : all_attributes)
	{
		if (relation_attribute.name == attribute_name)
			return index_of_attribute;
		index_of_attribute++;
	}

	return -1;
}
