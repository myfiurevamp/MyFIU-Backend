#pragma once
#include <vector>
#include "attribute.h"


typedef struct attributeList
{
public:
	attributeList();
	~attributeList();
	template <class InputIterator>
	attributeList(InputIterator first, InputIterator last) { setAllAttributes(first, last); }
	void addAttribute(attribute new_attribute);
	attribute getAttribute(int index);
	attribute getAttribute(std::string attribute_name);
	int getIndexOfAttribute(std::string attribute_name);
	int getNumOfAttributes();
	attribute operator[](int index) { return getAttribute(index); }

	std::vector<attribute> all_attributes;

	auto begin() -> decltype(all_attributes.begin()) { return all_attributes.begin(); }
	auto end() -> decltype(all_attributes.end()) { return all_attributes.end(); }

	template <class InputIterator>
	void setAllAttributes(InputIterator first, InputIterator last)
	{
		for (InputIterator all_attributes_iterator = first; all_attributes_iterator != last; all_attributes_iterator++)
		{
			attribute new_attribute = *all_attributes_iterator;
			all_attributes.push_back(new_attribute);
		}
	}


} attributeList;
