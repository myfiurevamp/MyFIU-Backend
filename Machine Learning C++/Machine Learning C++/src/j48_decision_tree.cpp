//#include "../../stdafx.h"
#include <iostream>
#include "../include/j48_decision_tree.h"
#include "../include/Entropy.h" // delete later

using namespace std;

J48DecisionTree::J48DecisionTree()
{
	impurity_measure = new Entropy(); // default impurity_measure to Entropy object
	// relation_obj not initialized
	// class_label not initialized

	//buildDecisionTree();
}

J48DecisionTree::J48DecisionTree(std::string _class_label)
{
	impurity_measure = new Entropy(); // default impurity_measure to Entropy object
	class_label = _class_label;
	// relation_obj not initialized
}

J48DecisionTree::J48DecisionTree(ImpurityMeasure * _impurity_measure, std::string _class_label)
{
	impurity_measure = _impurity_measure; // TODO: check if class of ImpurityMeasure object is concrete
	class_label = _class_label;
	// relation_obj not initialized
}

J48DecisionTree::J48DecisionTree(relation _relation_obj, std::string _class_label)
{
	relation_obj = _relation_obj;
	impurity_measure = new Entropy(); // default impurity_measure to Entropy object
	class_label = _class_label;

}

J48DecisionTree::J48DecisionTree(relation _relation_obj, ImpurityMeasure * _impurity_measure, std::string _class_label)
{
	impurity_measure = _impurity_measure; // TODO: check if class of ImpurityMeasure object is concrete
	class_label = _class_label;
	relation_obj = _relation_obj;
}


J48DecisionTree::~J48DecisionTree()
{
	//free all nodes!
}

void J48DecisionTree::setImpurityMeasure(ImpurityMeasure* _impurity_measure)
{
	impurity_measure = _impurity_measure;
}

void J48DecisionTree::buildDecisionTree()
{
	if (impurity_measure != NULL)
		cout << "not null\n";
	else cout << "null\n";

	impurity_measure->setRelation(relation_obj);

	class_label_impurity = impurity_measure->calculate_impurity(class_label_index);

	/* Find first attribute to split on */
	
	float attribute_impurity;
	int best_initial_attribute_index = impurity_measure->findBestInitalSplit(class_label_index, &attribute_impurity);
	vector<string> best_initial_attribute_values = relation_obj[best_initial_attribute_index].values;

	root = new j48_node(best_initial_attribute_index, best_initial_attribute_values, attribute_impurity);

	cout << "Information Gain: " << class_label_impurity - root->impurity << endl;


}

void J48DecisionTree::predict(attribute class_attribute)
{
	return;
}

float J48DecisionTree::getClassLabelImpurity()
{
	return class_label_impurity;
}
