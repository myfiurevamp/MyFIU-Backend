#pragma once
#include <string>
#include <vector>

//struct or class? struct: members public by default, class: members private by default

typedef struct j48_node_branch {

	std::string attribute_value_name;
	float attribute_value_impurity;
	struct j48_node* next; // maximum of one node

} j48_node_branch;


typedef struct j48_node {

	int attribute_index; // position of attribute in dataset_header 
	int node_fanout;
	float impurity; //necessary?
	bool is_leaf;
	struct j48_node_branch* branches;

	j48_node(int _attribute_index, std::vector<std::string> attribute_value_names, float _impurity) {
	
		attribute_index = _attribute_index;
		impurity = _impurity;
		node_fanout = attribute_value_names.size();
		branches = new j48_node_branch[node_fanout];

		for (int i = 0; i < node_fanout; i++)
			branches[i].attribute_value_name = attribute_value_names[i];
	
	}

} j48_node;


