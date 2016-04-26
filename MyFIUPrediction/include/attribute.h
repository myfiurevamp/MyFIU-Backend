#pragma once
#include <string>
#include <vector>
#include <iostream> //-- debug

#define decltype1() all_values.begin() 

struct attributeList;
struct attribute;

enum struct attribute_type
{
	NUMERIC,
	STRING,
	NOMINAL,
	DATE
};

typedef struct attribute {

public:
	std::string name;
	attribute_type type;
	std::vector<std::string> all_values;
	bool is_unique;

	template <class InputIterator>
	void setAllValues(InputIterator first, InputIterator last)
	{
		for (InputIterator all_values_iterator = first; all_values_iterator != last; all_values_iterator++)
		{
		        std::string value = *all_values_iterator;
			all_values.push_back(value);
		}

		is_unique = false;
	}

	void setUniqueness(bool _is_unique) { is_unique = _is_unique; }
	int getNumOfValues() { return all_values.size(); }


	auto begin() -> decltype(all_values.begin()) { return all_values.begin(); }
	auto end()  -> decltype(all_values.end()) { return all_values.end(); }

	bool operator==(const attribute &other) const 
	{
		if (name == other.name && type == other.type)
			return true;
		else
			return false;
	}

} attribute;
