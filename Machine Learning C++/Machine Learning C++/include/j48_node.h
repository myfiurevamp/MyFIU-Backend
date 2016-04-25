#pragma once
#include <string>
#include <vector>

//struct or class? struct: members public by default, class: members private by default

typedef struct j48_node_branch {

	j48_node_branch() { next = NULL; }
	~j48_node_branch() { delete next; }
	std::string attribute_value_name;
	float attribute_value_impurity;
	struct j48_node* next; // maximum of one node

} j48_node_branch;


typedef struct j48_node {

	j48_node() {};
	~j48_node() 
	{
		for (struct j48_node_branch* branch : branches)
			delete branch;
	}
	int attribute_index; // position of attribute in dataset_header 
	//int node_fanout;
	float impurity; //necessary?
	bool is_leaf;
	std::string class_label_value;
	std::vector<struct j48_node_branch*> branches;

	j48_node(int _attribute_index, attribute attr, float _impurity) {
	
		attribute_index = _attribute_index;
		impurity = _impurity;
		is_leaf = false;
		//node_fanout = attr.getNumOfValues();
		//branches = j48_node_branch[node_fanout];

		for (std::string attr_value_name : attr) 
		{
			j48_node_branch* new_branch = new j48_node_branch;
			new_branch->attribute_value_name = attr_value_name;
			branches.push_back(new_branch);
		}
	
	}

	void setAsLeafNode(std::string _class_label_value)
	{
		is_leaf = true;
		class_label_value = _class_label_value;

		//std::vector<j48_node_branch*>::iterator b = &branches.begin();

	}

	auto begin() -> decltype (branches.begin()) { return branches.begin(); }
	auto end() -> decltype (branches.end()) { return branches.end(); }


} j48_node;


