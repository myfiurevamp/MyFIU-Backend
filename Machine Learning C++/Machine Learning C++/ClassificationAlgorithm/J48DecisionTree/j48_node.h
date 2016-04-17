#pragma once
#include <string>

typedef struct struct_j48_node {

	std::string attribute_name; // or index?
	struct_j48_node* siblings;
	struct_j48_node* children;


} j48_node;