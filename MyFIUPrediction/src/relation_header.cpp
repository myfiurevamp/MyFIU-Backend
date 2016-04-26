#include "../include/relation_header.h"

using namespace std;

struct relationHeader;

relationHeader::relationHeader()
{
}

relationHeader::~relationHeader()
{
}

relationHeader::relationHeader(attributeList _all_attributes)
{
	all_attributes = _all_attributes;
}

int relationHeader::getIndexOfAttribute(string attribute_name)
{
	return all_attributes.getIndexOfAttribute(attribute_name);
}

int relationHeader::getNumOfColumns()
{
	return all_attributes.getNumOfAttributes();
}
