#pragma once
#include <string>
#include <vector>
#include <iostream> //-- debug

enum struct attribute_type
{
	NUMERIC,
	STRING,
	NOMINAL,
	DATE
};

typedef struct struct_attribute {

	std::string name;
	attribute_type type;
	std::vector<std::string> values;

} attribute;
