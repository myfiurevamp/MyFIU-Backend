#pragma once
#include <string>

typedef struct struct_j48_node {

	std::string attribute_name;
	j48_node* siblings;
	j48_node* children;


} j48_node;