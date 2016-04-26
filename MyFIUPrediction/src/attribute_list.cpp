#include "../include/attribute_list.h"
#include <stdexcept>

using namespace std;
attributeList::attributeList()
{
}


attributeList::~attributeList()
{
}


//template<class InputIterator>
//attributeList::attributeList(InputIterator first, InputIterator last)
//{
//	setAllValues(first, last);
//}


void attributeList::addAttribute(attribute new_attribute)
{
	all_attributes.push_back(new_attribute);
}

//template<class InputIterator>
//void attributeList::setAllAttributes(InputIterator first, InputIterator last)
//{
//	for (InputIterator all_attributes_iterator = first; all_attributes_iterator != last; all_attributes_iterator++)
//	{
//		attribute new_attribute = *all_attributes_iterator;
//		all_attributes.push_back(new_attribute);
//	}
//	
//}


attribute attributeList::getAttribute(int index)
{
	return all_attributes[index];
}

attribute attributeList::getAttribute(std::string attribute_name)
{
	attribute attr;

	for (auto all_attributes_iterator = all_attributes.begin(); all_attributes_iterator != all_attributes.end(); all_attributes_iterator++)
	{
		attr = *all_attributes_iterator;

		if (attr.name == attribute_name)
			return attr;
	}

	throw invalid_argument("Attribute " + attribute_name + " does not exist!");
}

int attributeList::getIndexOfAttribute(std::string attribute_name)
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

int attributeList::getNumOfAttributes()
{
	return all_attributes.size();
}


